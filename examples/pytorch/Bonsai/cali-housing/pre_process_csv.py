# import pandas as pd

# # Load the CSV file
# df = pd.read_csv('/home/siddhant/Documents/minor/EdgeML/examples/pytorch/Bonsai/cali-housing/big_housing.csv')

# # Randomly sample 1400 rows
# reduced_df = df.sample(n=1800)

# # Save the reduced dataset to a new CSV file
# reduced_df.to_csv('/home/siddhant/Documents/minor/EdgeML/examples/pytorch/Bonsai/cali-housing/housing.csv', index=False)

import pandas as pd

# Read the CSV file
df = pd.read_csv('housing.csv')

# Convert to LIBSVM format
with open('output_file.txt', 'w') as f:
    for index, row in df.iterrows():
        # The target value is in the 'median_house_value' column
        line = str(row['median_house_value'])
        # Iterate through all columns except the target
        for i, (col_name, value) in enumerate(row.items()):
            if col_name != 'median_house_value':  # Skip zero values for sparse representation
                line += f' {i+1}:{value}'
        f.write(line + '\n')
