#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
RUN_TEST () {
				echo -n "Testing on $1: "
				RES=$(../lem-in < ./cases/$1)
				EXPECT=$(cat ./cases/$1 | grep -m 1 'lines required' | awk 'NF>1{print $NF}')
				OUT=$(echo "$RES" | grep '^L' | wc -l)
				DIFF=$(echo "$OUT - $EXPECT" | bc)
				if [ $DIFF -lt 0 ]
				then
					echo -e "${RED}ERROR: Hmmm, something is off...${NC}"
				elif [ $DIFF -eq 0 ]
				then
					echo -e "${GREEN}OK${NC}"
				else
					echo -e "${RED}FAIL${NC}"
				fi
}

echo "Welcome to the ACCURACY GAUNTLET"
RUN_TEST augment_0.map
RUN_TEST augment_1.map
RUN_TEST augment_2.map
RUN_TEST augment_3.map
RUN_TEST augment_4.map
RUN_TEST augment_5.map
RUN_TEST augment_6.map
RUN_TEST augment_7.map
RUN_TEST augment_8.map
RUN_TEST augment_9.map
