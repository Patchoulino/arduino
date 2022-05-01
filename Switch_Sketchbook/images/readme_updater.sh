#!/bin/bash
rm README.md events_README.md
IFS=$'\n'; for i in $(ls shiny/*.jpg); do echo $i >> README.md; echo "\![]($i)" >> README.md; done
IFS=$'\n'; for i in $(ls shiny/events/*.jpg); do echo $i >> events_README.md; echo "\![]($i)" >> events_README.md; done
sed -i 's/\\//g' *README.md
sed -i "/^\!/s/ /%20/g" *README.md
