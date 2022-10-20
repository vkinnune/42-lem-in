MAP_DIR=./gen_map
ONE_DIR="$MAP_DIR"/flow_one
TEN_DIR="$MAP_DIR"/flow_ten
THOUSAND_DIR="$MAP_DIR"/flow_thousand
BIG_DIR="$MAP_DIR"/big
BIG_SUP_DIR="$MAP_DIR"/big_sup
GENERATOR=./generator

if [ ! -d "$MAP_DIR" ]
then
	mkdir "$MAP_DIR"
fi

if [ "$1" == "one" ]
then
	if [ ! -d "$ONE_DIR" ]
	then
		mkdir "$ONE_DIR"
	fi
	for i in {1..50}
	do
		"$GENERATOR" --flow-one > "$ONE_DIR/map_$i"
		sleep 1
	done
fi

if [ "$1" == "ten" ]
then
	if [ ! -d "$TEN_DIR" ]
	then
		mkdir "$TEN_DIR"
	fi
	for i in {1..50}
	do
		"$GENERATOR" --flow-ten > "$TEN_DIR/map_$i"
		sleep 1
	done
fi

if [ "$1" == "thousand" ]
then
	if [ ! -d "$THOUSAND_DIR" ]
	then
		mkdir "$THOUSAND_DIR"
	fi
	for i in {1..50}
	do
		"$GENERATOR" --flow-thousand > "$THOUSAND_DIR/map_$i"
		sleep 1
	done
fi

if [ "$1" == "big" ]
then
	if [ ! -d "$BIG_DIR" ]
	then
		mkdir "$BIG_DIR"
	fi
	for i in {1..50}
	do
		"$GENERATOR" --big> "$BIG_DIR/map_$i"
		sleep 1
	done
fi

if [ "$1" == "big_sup" ]
then
	if [ ! -d "$BIG_SUP_DIR" ]
	then
		mkdir "$BIG_SUP_DIR"
	fi
	for i in {1..50}
	do
		"$GENERATOR" --big-superposition > "$BIG_SUP_DIR/map_$i"
		sleep 1
	done
fi
