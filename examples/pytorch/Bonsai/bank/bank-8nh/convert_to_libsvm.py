def convert_to_libsvm(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            # Split the line into a list of values
            values = line.strip().split()

            # The last value is the target variable
            target = values[-1]

            # Create a list of "index:value" pairs for the features
            features = [f"{i + 1}:{v}" for i, v in enumerate(values[:-1])]

            # Join the target and features into the libsvm format
            libsvm_line = f"{target} {' '.join(features)}\n"

            # Write the line to the output file
            outfile.write(libsvm_line)

# Example usage
convert_to_libsvm('bank-8nh.txt', 'libsvm-formatted.txt')
