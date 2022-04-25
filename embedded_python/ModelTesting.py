import sys

if not hasattr(sys, 'argv'):
    sys.argv = ['']

import model as mmodel
import tensorflow as tf
import numpy as np
import sys

_IMG_WIDTH = 299
_IMG_HEIGHT = 299
"""classifies image and returns prediction

    Args:
     image: image (numpy array)
     modelPath: path to the trained model that will be used to classify image

    Returns:
      The result of classification (class number to which image belongs)

    Raises:

    """


def classify(image,model):
    image = tf.expand_dims(image, 0)  # Create a batch
    print("shape = {}".format(image.shape))
    predictions = model.predict(image)
    score = tf.nn.softmax(predictions[0])
    print("Predictions= {},shape ={}".format(predictions[0], predictions[0].shape))
    print("Score= {}".format(score))
    print(
        "This image most likely belongs to {} with a {:.2f} percent confidence."
            .format(np.argmax(score), 100 * np.max(score))
    )
    return np.argmax(score), predictions[0]

def classify_multiple_projections_and_get_response_vector(projections, modelPath, numOfClasses):
    model = mmodel.load(modelPath)
    score = np.zeros(numOfClasses)
    for image in projections:
        # print("image= {}".format(image))
        score = score + classify(image, model)[1]

    res = score.tolist()
    res.insert(0, np.argmax(score))

    return tuple(res)


def classify_path(imagePath, modelPath):
    img_array=classify_loadImage(imagePath)

    return classify(img_array, modelPath)

def classify_loadImage(imagePath):
    img = tf.keras.preprocessing.image.load_img(
        imagePath, target_size=(_IMG_WIDTH, _IMG_HEIGHT), color_mode="grayscale"
    )
    img_array = tf.keras.preprocessing.image.img_to_array(img)
    # np.set_printoptions(threshold=sys.maxsize)
    # print(img_array)
    img_array = tf.multiply(tf.cast(img_array, tf.float32), 1.0 / 255.0)

    return img_array
def classify_test():
    # res=classify_path("/home/radek/Projects/ImageClassifier/data/images/tree1.jpg","/home/radek/Projects/ImageClassifier/data/models/CNN_binary_Map_person_edited_3x3")
    img_batch=[]
    paths=["/home/radek/Projects/ImageClassifier/data/images/tree1.jpg",
     "/home/radek/Projects/ImageClassifier/data/images/tree.jpg"]
    for path in paths:
        img_arr=classify_loadImage(path)
        img_batch.append(img_arr)

    res = classify_multiple_projections_and_get_response_vector(img_batch,
        "/home/radek/Projects/ImageClassifier/data/models/CNN_binary_Map_person_edited_3x3", 5)
    print("CLASS = {}".format(res[0]))


if __name__ == '__main__':
    classify_test()
