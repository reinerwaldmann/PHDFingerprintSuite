for i in `find ./ -name "*.txt"`
 do
echo $(basename $i);
./PHDFRRBuilder  $i  "frrs/FRR"+$(basename $i)

 done

