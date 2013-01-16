# Simple Experiment Script
# by T.W.W. - Public Domain 2011

# Parse some command line input paramters, and verify they were set
numberOfRuns=$1
exptName=$2
outputFolder="data/output-$2"
runtimeFile="runtime-$2.txt"

if [ -z $exptName ]
then
  echo "ERROR: Requires 2 arguments: $0 [Num Runs] [param 1]"
  exit
fi

# Create directory for output files. Experiment will only be run if it will not overwrite an old data set
if [ -d $outputFolder ]; then
  echo "ERROR: Folder $outputFolder already exists."
  exit
else
  mkdir $outputFolder
fi

echo "Starting experiment with $numberOfRuns iterations and exptName =$exptName at " `date`

# Repeat the experiment $numberOfRuns times
for i in `seq $numberOfRuns`
do
  #check if you have already run this data set
  outputFile="$outputFolder/data-$exptName-$i.txt"
  if [ -s $outputFile ]
  then
    echo "WARNING: File $outputFile already exists -- skipping run $i"
    continue
  fi
  echo "Running iteration $i " `date`
  
  # Put the commands to actually run your program / system here
  (time make verify >& $outputFile) >>& $outputFolder/$runtimeFile
  # possibly put some clean up steps here or a sleep command if you want a delay between experiments
done

# Do any final cleanup here

echo "Finished at time " `date`
