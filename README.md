# NLP Project Installation & Usage Guide

## Prerequisites
- macOS, Windows, or Linux system.
- Git
- Miniconda or Anaconda
- JDK 15 or later.
- Python3 and pip3

## Installation Steps

### 1. Clone the Repository
```bash
git clone https://github.com/Tarun-Mittal-cell/IdentifierAugNLP
cd NLP_Project
```


### 2. Setting Up Code2vec
```bash
cd code2vec
git clone https://github.com/tech-srl/code2vec
wget https://s3.amazonaws.com/code2vec/data/java14m_data.tar.gz
tar -xvzf java14m_data.tar.gz
```
To preprocess a new dataset, edit the preprocess.sh file and run:
```bash
source preprocess.sh
```
To train a model from scratch, edit the train.sh file and run:
```bash
source train.sh
```

For evaluating a trained model:
```bash
python3 code2vec.py --load models/java14_model/saved_model_iter8.release --test data/java14m/java14m.test.c2v
```

To manually examine a trained model:
```bash
python3 code2vec.py --load models/java14_model/saved_model_iter8.release --predict
```

### 3. Setting Up ensemble_tagger
```bash
cd ensemble_tagger
git clone --recursive https://github.com/SCANL/ensemble_tagger.git
sudo pip3 install -r requirements.txt
export PYTHONPATH=~/path/to/ensemble_tagger/ensemble_tagger_implementation
```
Install Spiral:
```bash
sudo pip3 install git+https://github.com/casics/spiral.git
```

Start the ensemble_tagger server:
```bash
cd ensemble_tagger_implementation
python3 routes.py [MODEL]
```

### 4. Setting Up srcML
Navigate to srcML-1.0.0 and follow the instructions in BUILD.md or README.md.

## Usage

### 1. Preprocess Java Code with srcML
```bash
cd srcML-1.0.0
./src2srcml path_to_your_java_file -o output_file.xml
```

### 2. Analyze Event-Driven Code
```bash
cd Event\ Driven\ Code\ Examples
python event_analysis.py
```

### 3. Run code2vec
Navigate to the code2vec directory and run:
```bash
python3 code2vec.py --load models/java14_model/saved_model_iter8.release --predict
```

### 4. Run the ensemble_tagger
Ensure the ensemble_tagger server is running. Then, in a separate terminal, navigate to the scripts directory:
```bash
cd scripts
./grabidentifiers path_to_your_srcML_file.xml
```

### 5. Analyze Results
Review the results from the ensemble_tagger.

### 6. Run the Main Prototype
Navigate to the Expand directory:
```bash
cd Expand
java Main.java
```

## Troubleshooting
1. Ensure the correct Python environment is activated.
2. Double-check all installation steps.
3. Refer to README or documentation files in each directory.




## Credits

Special thanks to Dr. Christian Newman for his invaluable guidance throughout this project. Without his expertise and mentorship, this project would not have been possible. 

Additionally, immense gratitude is extended for allowing the use of the `ensemble_tagger`, which he authored. You can find more of his work on his GitHub account: [cnewman](https://github.com/cnewman).

## Feedback and Support
For questions, feedback, or support, contact tm6622@rit.edu or raise an issue on the GitHub repository.



