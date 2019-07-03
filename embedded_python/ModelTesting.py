import tensorflow as tf
import numpy

print("IM IN PYTHON ................")
#dla rozwiazania porblemu https://github.com/google/oauth2client/issues/642
#import sys
#if not hasattr(sys, 'argv'):
    #sys.argv  = ['']



tf.app.flags.DEFINE_integer('number_of_classes', 5,
                            'Number of classes (among which we will classify images) in taining and test dataset')
tf.app.flags.DEFINE_string('model_directory', './zapisane/CNN_range_3D_BIWI',    #'./data/train',                  #CNN_binary_3D_Map_person_1 #CNN_range_3D_BIWI #CNN_mapillary_SV
                           'Training data directory')

FLAGS = tf.app.flags.FLAGS

def classify(test):

    with tf.Session() as sess:

        test = tf.multiply(tf.cast(test, tf.float32), 1.0 / 255.0)
        test = tf.expand_dims(tf.expand_dims(test, axis=-1), axis=0)
        test = test.eval()
        print("test.shape: " + str(test.shape))

        #zaimportowanie wczesniej wyeksportowanego grafu
        saver = tf.train.import_meta_graph(FLAGS.model_directory+'/my-model.meta')
        saver.restore(sess, tf.train.latest_checkpoint(FLAGS.model_directory))

        #Pobranie operacji, tenosrow (elementy grafu, czyli tez modelu sieci) do ktorego ladujemy
        #interesujace nas operacje najepiej szukac na reprezetnacji graficznej zaimportowanego grafu w Tensorboard (np. w terminalu: tensorboard --logdir=/home/radek/DeepLearning/CNN_binaryensorboard_train/CNN_5warstwKonw   ,a nastepnie w przegladarce: http://localhost:6006  )
        next_element_image = tf.get_default_graph().get_operation_by_name('IteratorGetNext').outputs[0] # outputs[4] - daje next_element[4] - tensor do ktorego laduje sie labele - dane zapisane w next_element okreslone sa w CreateData.py
        pkeep = tf.get_default_graph().get_operation_by_name('Placeholder_1').outputs[0] #dla testowanie pkeep=1 (parametr do dropoutu)
        Y = tf.get_default_graph().get_operation_by_name('Softmax').outputs[0]  #Y warstwa wyjsciowa (czyli po softmax - wektor wartosci [0-1] okreslajacych przekonanie, ze dane naleza do klasy odpowiadajacej indexowi tego wektora
        print(next_element_image)

        Y_ = sess.run(Y, feed_dict={next_element_image: test,pkeep: 1})
        print(Y_)
        print("Wynik klasyfikacji: " + str(numpy.argmax(Y_)))
        return numpy.argmax(Y_)

def classify_multiple_projections(test,modelDirectory,number_of_classes): #clasify single object based on its multiple projections
    print("USING {} MODEL ".format(modelDirectory))

    with tf.Session() as sess:
        # zaimportowanie wczesniej wyeksportowanego grafu
        saver = tf.train.import_meta_graph(modelDirectory + '/my-model.meta')
        saver.restore(sess, tf.train.latest_checkpoint(modelDirectory))

        # Pobranie operacji, tenosrow (elementy grafu, czyli tez modelu sieci) do ktorego ladujemy
        # interesujace nas operacje najepiej szukac na reprezetnacji graficznej zaimportowanego grafu w Tensorboard (np. w terminalu: tensorboard --logdir=/home/radek/DeepLearning/CNN_binaryensorboard_train/CNN_5warstwKonw   ,a nastepnie w przegladarce: http://localhost:6006  )
        next_element_image = tf.get_default_graph().get_operation_by_name('IteratorGetNext').outputs[0]  # outputs[4] - daje next_element[4] - tensor do ktorego laduje sie labele - dane zapisane w next_element okreslone sa w CreateData.py
        pkeep = tf.get_default_graph().get_operation_by_name('Placeholder_1').outputs[0]  # dla testowanie pkeep=1 (parametr do dropoutu)
        Y = tf.get_default_graph().get_operation_by_name('Softmax').outputs[0]  # Y warstwa wyjsciowa (czyli po softmax - wektor wartosci [0-1] okreslajacych przekonanie, ze dane naleza do klasy odpowiadajacej indexowi tego wektora
        # print(next_element_image)

        max_sum = numpy.zeros((1,number_of_classes)) #uwaga, tu trzeba podac ilosc klas
        k=0
        #print("test_shape "+str(numpy.shape(test)))
        for image in test:

            image = tf.multiply(tf.cast(image, tf.float32), 1.0 / 255.0)
            image = tf.expand_dims(tf.expand_dims(image, axis=-1), axis=0)
            image = image.eval()
            #print("image.shape: " + str(image.shape))

            Y_ = sess.run(Y, feed_dict={next_element_image: image,pkeep: 1})
            """
            if(Y_[0,numpy.argmax(Y_)]<0.9):  #minimalna wartosc sily odpowiedzi dla danego rzutu, jezeli sila opowiedzi sieci (wystarczy dla jednego rzutu, z kilku, jednego obiektu - moze trzeba to mienic) jest mniejsza od tej wartosci to stwierdzamy, ze obiekt ma nieokreslona klase
                print("CNN response for projection number "+str(k)+ " of current object: " + str(Y_))
                print("No class: "+str(Y_[0,numpy.argmax(Y_)]))
                return -1
            """
            max_sum=max_sum+Y_
            print("CNN response for projection number " + str(k) + " of current object: " + str(Y_))
            k=k+1

        print("max_sum = "+str(max_sum))
        print("Wynik klasyfikacji: " + str(numpy.argmax(max_sum)))

    tf.reset_default_graph()
    return numpy.argmax(max_sum)

def classify_multiple_projections_and_get_response_vector(test,modelDirectory,number_of_classes): #clasify single object based on its multiple projections
    print("USING {} MODEL ".format(modelDirectory))

    with tf.Session() as sess:
        # zaimportowanie wczesniej wyeksportowanego grafu
        saver = tf.train.import_meta_graph(modelDirectory + '/my-model.meta')
        saver.restore(sess, tf.train.latest_checkpoint(modelDirectory))

        # Pobranie operacji, tenosrow (elementy grafu, czyli tez modelu sieci) do ktorego ladujemy
        # interesujace nas operacje najepiej szukac na reprezetnacji graficznej zaimportowanego grafu w Tensorboard (np. w terminalu: tensorboard --logdir=/home/radek/DeepLearning/CNN_binaryensorboard_train/CNN_5warstwKonw   ,a nastepnie w przegladarce: http://localhost:6006  )
        next_element_image = tf.get_default_graph().get_operation_by_name('IteratorGetNext').outputs[0]  # outputs[4] - daje next_element[4] - tensor do ktorego laduje sie labele - dane zapisane w next_element okreslone sa w CreateData.py
        pkeep = tf.get_default_graph().get_operation_by_name('Placeholder_1').outputs[0]  # dla testowanie pkeep=1 (parametr do dropoutu)
        Y = tf.get_default_graph().get_operation_by_name('Softmax').outputs[0]  # Y warstwa wyjsciowa (czyli po softmax - wektor wartosci [0-1] okreslajacych przekonanie, ze dane naleza do klasy odpowiadajacej indexowi tego wektora
        # print(next_element_image)

        max_sum = numpy.zeros((1,number_of_classes)) #uwaga, tu trzeba podac ilosc klas
        k=0
        #print("test_shape "+str(numpy.shape(test)))
        for image in test:

            image = tf.multiply(tf.cast(image, tf.float32), 1.0 / 255.0)
            image = tf.expand_dims(tf.expand_dims(image, axis=-1), axis=0)
            image = image.eval()
            #print("image.shape: " + str(image.shape))

            Y_ = sess.run(Y, feed_dict={next_element_image: image,pkeep: 1})
            """
            if(Y_[0,numpy.argmax(Y_)]<0.9):  #minimalna wartosc sily odpowiedzi dla danego rzutu, jezeli sila opowiedzi sieci (wystarczy dla jednego rzutu, z kilku, jednego obiektu - moze trzeba to mienic) jest mniejsza od tej wartosci to stwierdzamy, ze obiekt ma nieokreslona klase
                print("CNN response for projection number "+str(k)+ " of current object: " + str(Y_))
                print("No class: "+str(Y_[0,numpy.argmax(Y_)]))
                return -1
            """
            max_sum=max_sum+Y_
            print("CNN response for projection number " + str(k) + " of current object: " + str(Y_))
            k=k+1

        print("max_sum = "+str(max_sum))
        print("Wynik klasyfikacji: " + str(numpy.argmax(max_sum)))

    tf.reset_default_graph()

    result=max_sum[0].tolist()
    result.insert(0,numpy.argmax(max_sum))

    return tuple(result)


def main(unused_argv):

if __name__ == '__main__':
    tf.app.run()
