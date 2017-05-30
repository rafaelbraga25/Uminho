BEGIN {
	IGNORECASE = 1;
	fmtLI = "<li style=\"margin-left:50px\">%s</li>\n";
	fmtE = "<p></p><b style=\"font-size:150%\">%s</b>\n"; 
	fmtCD = "<p></p><b style=\"margin-left:25px\">%s</b>\n";
	FS = "^[> !<]*pt(_br)?(_pt)?";
	end = "</body></html>";
	print "<html><head><meta charset='UTF-8'/></head><body>" > "index.html";
}


/^pt/ || /^[>< !<]*pt/ {
	entry = removeWhiteSpaces($2);
}

/[> <!?]*def/ {
	split($0, target, "def");
	def = removeWhiteSpaces(target[2]);
	entries[entry][catg][def] = def;
}

/[> <!?-]*catgra/ {
	split($0, target, "catgra");
	catg = removeWhiteSpaces(target[2]);
}

END {
	for (i in entries) {
		if (length(i) > 1) {
		printf(fmtE, i) > "index.html";
		
		printf(fmtCD, "Categorias:") > "index.html";
		
		for (c in entries[i]) {
			if (length(c) > 1) {
				printf(fmtLI, c) > "index.html";
			}
		}

		printf(fmtCD, "Definições:") > "index.html";

		for (j in entries[i]) {
			for (w in entries[i][j]) {
					if (length(w) > 1) {
						printf(fmtLI, w) > "index.html";
					}
				} 
			}
		}
	}

	print end > "index.html";
}

function removeWhiteSpaces(str) {
	sub("\\t", "", str);
	sub("^ +", "", str);
	sub(" +$", "", str);

	return str;
}
