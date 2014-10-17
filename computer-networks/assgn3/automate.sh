ns ns-lab03.tcl
echo "FTP TPUT"
awk -f ftpTput.awk simple.tr
echo "FTP DELAY"
awk -f ftpDelays.awk simple.tr
echo "CBR TPUT"
awk -f cbrTput.awk simple.tr
echo "CBR DELAY"
awk -f cbrDelays.awk simple.tr
