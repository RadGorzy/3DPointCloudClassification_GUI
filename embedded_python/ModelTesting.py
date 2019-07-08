import tensorflow as tf
import numpy

print("IM IN PYTHON ................")
#to solve problem: https://github.com/google/oauth2client/issues/642
#import sys
#if not hasattr(sys, 'argv'):
    #sys.argv  = ['']



tf.app.flags.DEFINE_integer('number_of_classes', 5,
                            'Number of classes (among which we will classify images) in taining and test dataset')
tf.app.flags.DEFINE_string('model_directory', './zapisane/CNN_range_3D_BIWI',    #'./data/train',                  #CNN_binary_3D_Map_person_1 #CNN_range_3D_BIWI #CNN_mapillary_SV
                           'Training data directory')

FLAGS = tf.app.flags.FLAGS

def classify_multiple_projections_and_get_response_vector(test,modelDirectory,number_of_classes): #clasify single object based on its multiple projections
    print("USING {} MODEL ".format(modelDirectory))

    with tf.Session() as sess:
        # import previously exported graph
        saver = tf.train.import_meta_graph(modelDirectory + '/my-model.meta')
        saver.restore(sess, tf.train.latest_checkpoint(modelDirectory))

        # Getting operations, tensors (graph elements, neural net model elements) from loaded graph
        # Its best to look for operation of interest on graphical representation of imported graph in Tensorboard: (for ex. in terminal: tensorboard --logdir=/home/radek/DeepLearning/CNN_binaryensorboard_train/CNN_5warstwKonw   ,and then in browser: http://localhost:6006  )
        next_element_image = tf.get_default_graph().get_operation_by_name('IteratorGetNext').outputs[0]  # outputs[4] - gives next_element[4] - tensor to which we load labels - date saved in  next_element is defined in CreateData.py
        pkeep = tf.get_default_graph().get_operation_by_name('Placeholder_1').outputs[0]  #for tessting pkeep=1 (dropout parameter)
        Y = tf.get_default_graph().get_operation_by_name('Softmax').outputs[0]  # Y output layer (after softmax - vector of values [0-1] describing the belief that data belong to class represented by index of this vector
        # print(next_element_image)

        max_sum = numpy.zeros((1,number_of_classes))
        k=0
        #print("test_shape "+str(numpy.shape(test)))
        for image in test:

            image = tf.multiply(tf.cast(image, tf.float32), 1.0 / 255.0)
            image = tf.expand_dims(tf.expand_dims(image, axis=-1), axis=0)
            image = image.eval()
            #print("image.shape: " + str(image.shape))

            Y_ = sess.run(Y, feed_dict={next_element_image: image,pkeep: 1})
            """
            if(Y_[0,numpy.argmax(Y_)]<0.9):  #if lower then minimum response strength for given projection -> it belongs to unknown class
                print("CNN response for projection number "+str(k)+ " of current object: " + str(Y_))
                print("No class: "+str(Y_[0,numpy.argmax(Y_)]))
                return -1
            """
            max_sum=max_sum+Y_
            print("CNN response for projection number " + str(k) + " of current object: " + str(Y_))
            k=k+1

        print("max_sum = "+str(max_sum))
        print("Classification result: " + str(numpy.argmax(max_sum)))

    tf.reset_default_graph()

    result=max_sum[0].tolist()
    result.insert(0,numpy.argmax(max_sum))

    return tuple(result)

def main(unused_argv):
    print("test")

if __name__ == '__main__':
    tf.app.run()
