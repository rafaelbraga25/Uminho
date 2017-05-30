BEGIN {
	IGNORECASE = 1;
	FS = "^[&> !<]*dom +";
}

/^[&>< !]*dom / && length($2) > 0 {
	dom[norm($2)]++;
}

END {
	for (i in dom) {
		print i ": " dom[i];
	}
}

function norm(str) {
	sub("^ +", "", str);
	sub(" +$", "", str);
	return tolower(str);
}
