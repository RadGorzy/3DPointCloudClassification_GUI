//
// Created by radek on 16.03.19.
//
#include "src/model/segmentation.h"

#include <pcl/search/organized.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/extract_indices.h> //do wydobywania usunietej czesci chmury
#include <pcl/features/don.h>
#include <pcl/filters/voxel_grid.h> //do aproksymacji
#include <vector>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/pcd_io.h>
std::string CLOUD_NAME="_CLOUD_NAME_";//->? TYMCZASOWE ROZWIAZANIE - nazwa chmury wyswietlana w visualizerach
std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  SegmentationType::segment(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){throw std::runtime_error ("Operation not supported for this SegmentationType class");}
pcl::PointCloud<pcl::PointNormal> SegmentationType::getDonCloud(){throw std::runtime_error ("Operation not supported for this SegmentationType class");}

DONSegmentation::DONSegmentation(double scale1,double scale2, double threshold,double segradius,bool approx,double decimation,bool TWO_STEP_SEGMENTATION, double scale1_1, double scale2_1)
:scale1(scale1),scale2(scale2),threshold(threshold),segradius(segradius),approx(approx),decimation(decimation),TWO_STEP_SEGMENTATION(TWO_STEP_SEGMENTATION),scale1_1(scale1_1),scale2_1(scale2_1){}
std::vector<pcl::PointCloud<pcl::PointNormal>::Ptr> DONSegmentation::calculateDONAndFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_) {
    std::cout << "Segmenting Pointcloud with " << cloud_->points.size () << " data points." << std::endl;
    std::vector<pcl::PointCloud<pcl::PointNormal>::Ptr> filtred_and_removed;//filtred_and_removed[0]- fragment chmury spelniajacy warunek filtracji (don>=threshold)
    //filtred_and_removed[0]-pozostaly fragment chmury (usuniety w wyniku filtracji)

    // Create a search tree, use KDTreee for non-organized data.
    pcl::search::Search<pcl::PointXYZ>::Ptr tree;
    if (cloud_->isOrganized ())
    {
        tree.reset (new pcl::search::OrganizedNeighbor<pcl::PointXYZ> ());
    }
    else
    {
        tree.reset (new pcl::search::KdTree<pcl::PointXYZ> (false));
    }

    // Set the input pointcloud for the search tree
    tree->setInputCloud (cloud_);

    //Jezeli parapetr approx = 1 - przerzedzanie chmury
    pcl::PointCloud<pcl::PointXYZ>::Ptr small_cloud_downsampled;
    pcl::PointCloud<pcl::PointXYZ>::Ptr large_cloud_downsampled;

    if(approx){
        std::cout << "Downsampling point cloud_ for approximation" << std::endl;

        // Create the downsampling filtering object
        pcl::VoxelGrid<pcl::PointXYZ> sor;
        sor.setDownsampleAllData (false);
        sor.setInputCloud (cloud_);

        // Create downsampled point cloud for DoN NN search with small scale
        small_cloud_downsampled = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
        float smalldownsample = static_cast<float> (scale1 / decimation);
        //Eigen::Vector3f leafsize= sor.getLeafSize();
        sor.setLeafSize (smalldownsample, smalldownsample, smalldownsample);
        sor.filter (*small_cloud_downsampled);
        std::cout << "Using leaf size of " << smalldownsample << " for small scale, " << small_cloud_downsampled->size() << " points" << std::endl;

        // Create downsampled point cloud for DoN NN search with large scale
        large_cloud_downsampled = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
        float largedownsample = float (scale2/decimation);
        sor.setLeafSize (largedownsample, largedownsample, largedownsample);
        sor.filter (*large_cloud_downsampled);

        std::cout << "Using leaf size of " << largedownsample << " for large scale, " << large_cloud_downsampled->size() << " points" << std::endl;
    }

    //wizualizacja chmur dla ktorych licze normalne oparte na maly i duzym promieniu
    if(VISUALIZE_NORMALS)
    {
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_downsampled (new pcl::visualization::PCLVisualizer ("Downsample"));
        int v0(0);
        int v1(0);
        int v2(0);
        viewer_downsampled->createViewPort(0.0,0.0,0.5,1.0,v1);//create the first view port
        viewer_downsampled->createViewPort(0.5,0.0,1.0,1.0,v2);//create the secondview port+
        viewer_downsampled->setCameraPosition	(0,0,100,0,0,0);

        viewer_downsampled->setBackgroundColor (0, 0, 0); //biale tlo, bo punkty byly czarne - wrazie braku widocznosci punktow zmienic tlo na czarne (0,0,0)
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(small_cloud_downsampled, 0, 255, 0);
        viewer_downsampled->addPointCloud (small_cloud_downsampled, single_color, "small_cloud_downsampled",v1);
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color_1(small_cloud_downsampled, 0, 0, 255);
        viewer_downsampled->addPointCloud (large_cloud_downsampled, single_color, "large_cloud_downsampled",v2);
        while (!viewer_downsampled->wasStopped ())
        {
            viewer_downsampled->spinOnce (100);
        }
    }



    if (scale1 >= scale2)
    {
        std::cerr << "Error: Large scale must be > small scale!" << std::endl;
        exit (EXIT_FAILURE);
    }

    // Compute normals using both small and large scales at each point
    pcl::NormalEstimationOMP<pcl::PointXYZ, pcl::PointNormal> ne; // -wykorzystuje wiele rdzeni procesora, jest jeszcze pcl::gpu::NormalEstimation - wykorzystuje GPU
    ne.setInputCloud (cloud_);
    ne.setSearchMethod (tree);

    /**
     * NOTE: setting viewpoint is very important, so that we can ensure
     * normals are all pointed in the same direction!
     */
    ne.setViewPoint (std::numeric_limits<float>::max (), std::numeric_limits<float>::max (), std::numeric_limits<float>::max ());
    /**/
    if(scale1 >= scale2){
        std::cerr << "Error: Large scale must be > small scale!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // calculate normals with the small scale
    std::cout << "Calculating normals for scale..." << scale1 << std::endl;
    pcl::PointCloud<pcl::PointNormal>::Ptr normals_small_scale (new pcl::PointCloud<pcl::PointNormal>);

    if(approx){
        ne.setSearchSurface(small_cloud_downsampled);
    }

    ne.setRadiusSearch (scale1);
    ne.compute (*normals_small_scale);

    // calculate normals with the large scale
    std::cout << "Calculating normals for scale..." << scale2 << std::endl;
    pcl::PointCloud<pcl::PointNormal>::Ptr normals_large_scale (new pcl::PointCloud<pcl::PointNormal>);

    if(approx){
        ne.setSearchSurface(large_cloud_downsampled);
    }

    ne.setRadiusSearch (scale2);
    ne.compute (*normals_large_scale);

    if(VISUALIZE_NORMALS)
    {
        int vns(0);

        int vnl(0);


        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewern1 (new pcl::visualization::PCLVisualizer ("Normals small vs large scale Viewer"));
        viewern1->createViewPort(0.0,0.0,0.5,1.0,vns);//create the first view port
        viewern1->createViewPort(0.5,0.0,1.0,1.0,vnl);//create the secondview port+

        viewern1->setBackgroundColor(0,0,0);
        viewern1->addPointCloudNormals<pcl::PointXYZ, pcl::PointNormal> (cloud_, normals_small_scale, 50, 2, "normals small scale",vns);
        viewern1->addPointCloudNormals<pcl::PointXYZ, pcl::PointNormal> (cloud_, normals_large_scale, 50, 2, "normals large scale",vnl);
        while (!viewern1->wasStopped ())
        {
            viewern1->spinOnce (100);
        }

    }

    // Create output cloud for DoN results
    pcl::PointCloud<pcl::PointNormal>::Ptr doncloud_ (new pcl::PointCloud<pcl::PointNormal>);
    pcl::copyPointCloud<pcl::PointXYZ, pcl::PointNormal>(*cloud_, *doncloud_);

    std::cout << "Calculating DoN... " << std::endl;

    // Create DoN operator
    pcl::DifferenceOfNormalsEstimation<pcl::PointXYZ, pcl::PointNormal, pcl::PointNormal> don;
    don.setInputCloud (cloud_);
    don.setNormalScaleLarge (normals_large_scale);
    don.setNormalScaleSmall (normals_small_scale);

    if (!don.initCompute ())
    {
        std::cerr << "Error: Could not intialize DoN feature operator" << std::endl;
        exit (EXIT_FAILURE);
    }

    // Compute DoN
    don.computeFeature (*doncloud_);

    std::cout << "Computed DoN futures, doncloud_ has " << doncloud_->points.size () << " data points." << std::endl;
    pcl::PCDWriter writer;
    if(SAVE)
    {
        // Save DoN features
        std::cout << "Saving DoN futures, doncloud_ has " << doncloud_->points.size () << " data points." << std::endl;
        writer.write<pcl::PointNormal> ("don"+CLOUD_NAME+".pcd", *doncloud_, false);
        std::cout << "Saved DoN futures to don.pcd " << std::endl;
    }
    //wizualizacja normalnych:
    if(VISUALIZE_NORMALS)
    {
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewern (new pcl::visualization::PCLVisualizer ("Normals Viewer"));
        viewern->setBackgroundColor(0,0,0);
        viewern->addPointCloud(cloud_,"chmurka",0);
        viewern->addPointCloudNormals<pcl::PointXYZ, pcl::PointNormal> (cloud_, doncloud_, 50, 2, "normals");
        while (!viewern->wasStopped ())
        {
            viewern->spinOnce (100);
        }
    }
    // Filter by magnitude
    std::cout << "Filtering out DoN mag <= " << threshold << "..." << std::endl;

    // Build the condition for filtering
    pcl::ConditionOr<pcl::PointNormal>::Ptr range_cond (
            new pcl::ConditionOr<pcl::PointNormal> ()
    );
    range_cond->addComparison (pcl::FieldComparison<pcl::PointNormal>::ConstPtr (
            new pcl::FieldComparison<pcl::PointNormal> ("curvature", pcl::ComparisonOps::GT, threshold)) // zostawiamy tylko te punkty, ktore maja operator delta n(P) wiekszy od 0.25. - powstaja oddzielne obszary chmury
    );
    // Build the filter
    pcl::ConditionalRemoval<pcl::PointNormal> condrem (true); // Initializing with true will allow us to extract the removed indices;
    condrem.setCondition(range_cond);
    condrem.setInputCloud (doncloud_);

    pcl::PointCloud<pcl::PointNormal>::Ptr doncloud_filtered (new pcl::PointCloud<pcl::PointNormal>);

    // Apply filter
    condrem.filter (*doncloud_filtered);

    pcl::PointCloud<pcl::PointNormal>::Ptr removed (new pcl::PointCloud<pcl::PointNormal>);
    if(TWO_STEP_SEGMENTATION)
    {
        pcl::PointIndices::Ptr indices (new pcl::PointIndices ());
        condrem.getRemovedIndices(*indices);

        pcl::ExtractIndices<pcl::PointNormal> extractIndices;
        extractIndices.setIndices(indices);
        extractIndices.setInputCloud(doncloud_);
        extractIndices.setNegative(false);
        extractIndices.filter(*removed);
        std::cout<<"Removed cloud size= "<<removed->size()<<std::endl;

        if(SAVE)
        {
            std::cout<<"SAVING REMOVED CLOUD "<<std::endl;
            writer.write<pcl::PointNormal> ("removed"+CLOUD_NAME+".pcd", *removed, false);
        }
    }

    doncloud_ = doncloud_filtered;

    // Save filtered output
    std::cout << "Filtered Pointcloud: " << doncloud_->points.size () << " data points." << std::endl;
    if(SAVE)
        writer.write<pcl::PointNormal> ("don_filtered"+CLOUD_NAME+".pcd", *doncloud_, false);

    filtred_and_removed.push_back(doncloud_);
    if(TWO_STEP_SEGMENTATION)
    {
        filtred_and_removed.push_back(removed);
    }


    return filtred_and_removed;
}
void DONSegmentation::cluster(){
    clusterIndices.clear(); //WE CLEAR this vector, so when we use SegmentationType multiple times (instead of creating new ones) we have only current indecies. Otherwise we would have also indecies from previous scenes waht would cause problems
    // Filter by magnitude
    std::cout << "Clustering using EuclideanClusterExtraction with tolerance <= " << segradius << "..." << std::endl;

    pcl::search::KdTree<pcl::PointNormal>::Ptr segtree (new pcl::search::KdTree<pcl::PointNormal>);
    segtree->setInputCloud (doncloud);

    //std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointNormal> ec;
    ec.setClusterTolerance (segradius);
    ec.setMinClusterSize (50); //200
    ec.setMaxClusterSize (4000000); //100000 12.08.2018
    ec.setSearchMethod (segtree);
    ec.setInputCloud (doncloud);
    ec.extract (clusterIndices);
    //printf("found %s clusters",cluster_indices.size());
    std::cout<<"Found "<<clusterIndices.size()<<" objects in "<<CLOUD_NAME<<std::endl;
    std::cout<<"Size of cluster indices "<< sizeof(clusterIndices)<<std::endl;
    std::cout<<"sizeof(clusterIndices)*clusterIndices.size() = "<<sizeof(clusterIndices)*clusterIndices.size()<<std::endl;

}
std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  DONSegmentation::segment(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    this->cloud=cloud;

    bool VISUALIZE=false;
    bool SAVE=false;
    std::vector<pcl::PointCloud<pcl::PointNormal>::Ptr> filtred_and_removed;//filtred_and_removed[0]- fragment chmury spelniajacy warunek filtracji (don>=threshold)
    //filtred_and_removed[0]-pozostaly fragment chmury (usuniety w wyniku filtracji)
    pcl::PointCloud<pcl::PointNormal>::Ptr doncloud1;

    filtred_and_removed=calculateDONAndFilter(this->cloud);
    doncloud1=filtred_and_removed[0];
    if(TWO_STEP_SEGMENTATION) //filtrujemy usuniety wczesniej fragment chmury (czylu najpierw wydobywamy duze obiekty - np. budynki), nastepnie tutaj segmentujemy pozostala czesc (zawierajaca juz np. tylko podloze i male obiekty)
    {
        std::cout<<"SECEOND STEP OF SEGMENTATION"<<std::endl;
        std::vector<pcl::PointCloud<pcl::PointNormal>::Ptr> filtred_and_removed1;
        pcl::PointCloud<pcl::PointNormal>::Ptr doncloud2;
        pcl::PointCloud<pcl::PointNormal>::Ptr removed;
        pcl::PointCloud<pcl::PointXYZ>::Ptr removed_xyz (new pcl::PointCloud<pcl::PointXYZ>);
        removed=filtred_and_removed[1];
        copyPointCloud(*removed, *removed_xyz);
        filtred_and_removed1=calculateDONAndFilter(removed_xyz);
        doncloud2=filtred_and_removed1[0];
        std::cout<<"SUMMING CLOUDS"<<std::endl;
        *doncloud=*doncloud1+*doncloud2;
    }
    else
        doncloud=doncloud1;

    cluster(); //acquire clusterIndices
    //create clouds from clusterIndices:
    std::cout<<"Creating clouds from clusters..."<<std::endl;
    int j = 0;

    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> cloudObjects;

    for (std::vector<pcl::PointIndices>::const_iterator it = clusterIndices.begin (); it != clusterIndices.end (); ++it, j++) {
        pcl::PointCloud<pcl::PointNormal>::Ptr cloud_cluster_don(new pcl::PointCloud<pcl::PointNormal>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz (new pcl::PointCloud<pcl::PointXYZ>); //for conversion from PointCloud<PointNormal> to PointClous<PointXYZ>
        //->? cloud_xyz-> za kazdym razem trzeba tworzyc nowy obiket (i wskaznik) bo inaczej caly czas wskazujemy na to samo miejsce w pamieci, i tylko zmienamy w tym miejscu chmury (przez co pamietamy tylko ostatnia)
        for (auto pit = it->indices.begin(); pit != it->indices.end(); ++pit) {
            cloud_cluster_don->points.push_back(
                    doncloud->points[*pit]); //it is necessary here to use doncloud (PointCloud<PointNormal>), it wont work with PointXYZ cloud because clusterIndecies where retrived using: pcl::EuclideanClusterExtraction<pcl::PointNormal> ec
        }                                                                  //so clusterIndices holds indecies of PointNormal

        cloud_cluster_don->width = static_cast<uint32_t >(cloud_cluster_don->points.size());
        cloud_cluster_don->height = 1;
        cloud_cluster_don->is_dense = true;

        pcl::copyPointCloud<pcl::PointNormal, pcl::PointXYZ>(*cloud_cluster_don,
                                                             *cloud_xyz); //konwersja z typu PointNormal do PointXY

        cloudObjects.push_back(cloud_xyz);
    }

    return cloudObjects;
}
pcl::PointCloud<pcl::PointNormal> DONSegmentation::getDonCloud(){return *(this->doncloud);}

