import subprocess

# Set the path to your code2vec repository
code2vec_path = "../code2vec"

# Set the path to the Java file you want to analyze
java_file_path = "./Event Driven Code Examples/Example1.java"

# Run code2vec on the Java file
with subprocess.Popen(
        f"python {code2vec_path}/interactive_predict.py {code2vec_path}/models/java14_model/saved_model_iter8.release --file {java_file_path}",
        shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
) as proc:
    # Capture the output and error messages of the script
    output, error = proc.communicate()
    
# Print the output and error messages
print("Output:")
print(output)
print("Error:")
print(error)
