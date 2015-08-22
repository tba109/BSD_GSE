MOST_RECENT_FILE=`ls bsd_raw_data*.txt | sort -n -t _ -k 2 | tail -1`
./analyze.sh $MOST_RECENT_FILE
