	if (($codespell || $help) && which("codespell") ne "" && which("python") ne "") {
		my $codespell_dict = `python -c "$python_codespell_dict" 2> /dev/null`;
	$typeKernelTypedefs\b
	(?:SKCIPHER_REQUEST|SHASH_DESC|AHASH_REQUEST)_ON_STACK\s*\(
					      "Co-developed-by: should not be used to attribute nominal patch author '$author'\n" . "$here\n" . $rawline);
					     "Co-developed-by: must be immediately followed by Signed-off-by:\n" . "$here\n" . $rawline);
				} elsif ($rawlines[$linenr] !~ /^\s*signed-off-by:\s*(.*)/i) {
					     "Co-developed-by: must be immediately followed by Signed-off-by:\n" . "$here\n" . $rawline . "\n" .$rawlines[$linenr]);
					     "Co-developed-by and Signed-off-by: name/email do not match \n" . "$here\n" . $rawline . "\n" .$rawlines[$linenr]);
		      $line =~ /^\s*(?:[\w\.\-]+\/)++[\w\.\-]+:/ ||
		      $line =~ /^\s*(?:Fixes:|Link:|$signature_tags)/i ||
					# A Fixes: or Link: line or signature tag line
			     "Possible unwrapped commit description (prefer a maximum 75 chars per line)\n" . $herecurr);
			my $length = 0;
			my $cnt = $realcnt;
			my $ln = $linenr + 1;
			my $f;
			my $is_start = 0;
			my $is_end = 0;
			for (; $cnt > 0 && defined $lines[$ln - 1]; $ln++) {
				$f = $lines[$ln - 1];
				$cnt-- if ($lines[$ln - 1] !~ /^-/);
				$is_end = $lines[$ln - 1] =~ /^\+/;
				last if (!$file && $f =~ /^\@\@/);
				if ($lines[$ln - 1] =~ /^\+\s*(?:bool|tristate|prompt)\s*["']/) {
					$is_start = 1;
				} elsif ($lines[$ln - 1] =~ /^\+\s*(?:---)?help(?:---)?$/) {
					$length = -1;
				$f =~ s/^.//;
				$f =~ s/#.*//;
				$f =~ s/^\s+//;
				next if ($f =~ /^$/);
				if ($f =~ /^\s*(?:config|menuconfig|choice|endchoice|
						  if|endif|menu|endmenu|source)\b/x) {
					$is_end = 1;
				$length++;
			if ($is_start && $is_end && $length < $min_conf_desc_length) {
				     "please write a paragraph that describes the config symbol fully\n" . $herecurr);
			#print "is_start<$is_start> is_end<$is_end> length<$length>\n";
				} elsif ($realfile =~ /\.(c|dts|dtsi)$/) {
					    not $spdx_license =~ /GPL-2\.0.*BSD-2-Clause/) {
		if ($rawline =~ /^\+.*\Q$realfile\E/) {
		next if ($realfile !~ /\.(h|c|s|S|sh|dtsi|dts)$/);
			    (show_type("LONG_LINE") || show_type($msg_type))) {
			     "Avoid using '.L' prefixed local symbol names for denoting a range of code via 'SYM_*_START/END' annotations; see Documentation/asm-annotations.rst\n" . $herecurr);
# Block comment styles
# Networking with an initial /*
		if ($realfile =~ m@^(drivers/net/|net/)@ &&
		    $prevrawline =~ /^\+[ \t]*\/\*[ \t]*$/ &&
		    $rawline =~ /^\+[ \t]*\*/ &&
		    $realline > 3) { # Do not warn about the initial copyright comment block after SPDX-License-Identifier
			WARN("NETWORKING_BLOCK_COMMENT_STYLE",
			     "networking block comments don't use an empty /* line, use /* Comment...\n" . $hereprev);
		}

		      $line =~ /^\+\s*EXPORT_SYMBOL/ ||
# avoid BUG() or BUG_ON()
		if ($line =~ /\b(?:BUG|BUG_ON)\b/) {
				      "Avoid crashing the kernel - try using WARN_ON & recovery code rather than BUG() or BUG_ON()\n" . $herecurr);
				asm|__asm__)$/x)
				ERROR("TRAILING_STATEMENTS",
				      "trailing statements should be on next line\n" . $herecurr . $stat_real);
				while ($var =~ m{($Ident)}g) {
					WARN("VSPRINTF_POINTER_EXTENSION",
					     "$ext_type vsprintf pointer extension '$bad_specifier'$use\n" . "$here\n$stat_real\n");
			     "Prefer strscpy over strlcpy - see: https://lore.kernel.org/r/CAHk-=wgfRnXz0W3D37d01q3JFkr_i_uTL=V6A6G1oUZcprmknw\@mail.gmail.com/\n" . $herecurr);
# check for k[mz]alloc with multiplies that could be kmalloc_array/kcalloc
		    $stat =~ /^\+\s*($Lval)\s*\=\s*(?:$balanced_parens)?\s*(k[mz]alloc)\s*\(\s*($FuncArg)\s*\*\s*($FuncArg)\s*,/) {
					$fixed[$fixlinenr] =~ s/\b($Lval)\s*\=\s*(?:$balanced_parens)?\s*(k[mz]alloc)\s*\(\s*($FuncArg)\s*\*\s*($FuncArg)/$1 . ' = ' . "$newfunc(" . trim($r1) . ', ' . trim($r2)/e;
		if ($line =~ /\b((?:devm_)?(?:kcalloc|kmalloc_array))\s*\(\s*sizeof\b/) {