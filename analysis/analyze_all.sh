ls *.txt > LIST
file=`cat LIST`
for line in $file
do ./analyze.sh $line
done
