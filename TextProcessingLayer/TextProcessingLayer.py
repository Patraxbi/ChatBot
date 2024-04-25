import random
answers = ["Hello again", "Howdy", "Go away", "The agony"]

# Main function accessed by interface layer
def text_processing_layer(question: str):
    x = random.randint(0, 3)
    return answers[x]