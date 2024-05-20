import random

def split_data(input_file, train_file, test_file, test_ratio=0.2):
    # Read the data from the file
    with open(input_file, 'r') as file:
        data = file.readlines()

    # Shuffle the data to randomize it
    random.shuffle(data)

    # Split the data into training and testing sets
    split_index = int(len(data) * test_ratio)
    test_data = data[:split_index]
    train_data = data[split_index:]

    # Write the training and testing data to separate files
    with open(train_file, 'w') as file:
        file.writelines(train_data)

    with open(test_file, 'w') as file:
        file.writelines(test_data)

    print(f"Data split completed. Training data: {len(train_data)} lines, Testing data: {len(test_data)} lines")

# Usage
input_file = 'bank-8nm.txt'  # Replace with the path to your input data file
train_file = 'train.txt'    # Path to save the new training data
test_file = 'test.txt'          # Path to save the testing data

split_data(input_file, train_file, test_file)
