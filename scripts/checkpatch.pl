my $chk_fixes_tag = 1;
my %maybe_linker_symbol; # for externs in c exceptions, when seen in *vmlinux.lds.h

  --no-fixes-tag             do not check for 'Fixes:' tag
	'fixes-tag!'	=> \$chk_fixes_tag,
	if (($codespell || $help) && which("python3") ne "") {
		my $codespell_dict = `python3 -c "$python_codespell_dict" 2> /dev/null`;
			__aligned\s*\(.*\)|
our $typeStdioTypedefs = qr{(?x:
	FILE
)};
	$typeKernelTypedefs\b|
	$typeStdioTypedefs\b
our @link_tags = qw(Link Closes);

#Create a search and print patterns for all these strings to be used directly below
our $link_tags_search = "";
our $link_tags_print = "";
foreach my $entry (@link_tags) {
	if ($link_tags_search ne "") {
		$link_tags_search .= '|';
		$link_tags_print .= ' or ';
	}
	$entry .= ':';
	$link_tags_search .= $entry;
	$link_tags_print .= "'$entry'";
}
$link_tags_search = "(?:${link_tags_search})";

our $obsolete_archives = qr{(?xi:
	\Qfreedesktop.org/archives/dri-devel\E |
	\Qlists.infradead.org\E |
	\Qlkml.org\E |
	\Qmail-archive.com\E |
	\Qmailman.alsa-project.org/pipermail\E |
	\Qmarc.info\E |
	\Qozlabs.org/pipermail\E |
	\Qspinics.net\E
)};

	"kmap"					=> "kmap_local_page",
	"kunmap"				=> "kunmap_local",
	"kmap_atomic"				=> "kmap_local_page",
	"kunmap_atomic"				=> "kunmap_local",
	(?:SKCIPHER_REQUEST|SHASH_DESC|AHASH_REQUEST)_ON_STACK\s*\(|
	(?:$Storage\s+)?(?:XA_STATE|XA_STATE_ORDER)\s*\(
$chk_fixes_tag = 0 if ($file);
	my $fixes_tag = 0;
	my $is_revert = 0;
	my $needs_fixes_tag = "";
					      "Co-developed-by: should not be used to attribute nominal patch author '$author'\n" . $herecurr);
					     "Co-developed-by: must be immediately followed by Signed-off-by:\n" . $herecurr);
				} elsif ($rawlines[$linenr] !~ /^signed-off-by:\s*(.*)/i) {
					     "Co-developed-by: must be immediately followed by Signed-off-by:\n" . $herecurr . $rawlines[$linenr] . "\n");
					     "Co-developed-by and Signed-off-by: name/email do not match\n" . $herecurr . $rawlines[$linenr] . "\n");
				}
			}

# check if Reported-by: is followed by a Closes: tag
			if ($sign_off =~ /^reported(?:|-and-tested)-by:$/i) {
				if (!defined $lines[$linenr]) {
					WARN("BAD_REPORTED_BY_LINK",
					     "Reported-by: should be immediately followed by Closes: with a URL to the report\n" . $herecurr . "\n");
				} elsif ($rawlines[$linenr] !~ /^closes:\s*/i) {
					WARN("BAD_REPORTED_BY_LINK",
					     "Reported-by: should be immediately followed by Closes: with a URL to the report\n" . $herecurr . $rawlines[$linenr] . "\n");
				}
			}
		}

# These indicate a bug fix
		if (!$in_header_lines && !$is_patch &&
			$line =~ /^This reverts commit/) {
			$is_revert = 1;
		}

		if (!$in_header_lines && !$is_patch &&
		    $line =~ /((?:(?:BUG: K.|UB)SAN: |Call Trace:|stable\@|syzkaller))/) {
			$needs_fixes_tag = $1;
		}

# Check Fixes: styles is correct
		if (!$in_header_lines &&
		    $line =~ /^\s*fixes:?\s*(?:commit\s*)?[0-9a-f]{5,}\b/i) {
			my $orig_commit = "";
			my $id = "0123456789ab";
			my $title = "commit title";
			my $tag_case = 1;
			my $tag_space = 1;
			my $id_length = 1;
			my $id_case = 1;
			my $title_has_quotes = 0;
			$fixes_tag = 1;

			if ($line =~ /(\s*fixes:?)\s+([0-9a-f]{5,})\s+($balanced_parens)/i) {
				my $tag = $1;
				$orig_commit = $2;
				$title = $3;

				$tag_case = 0 if $tag eq "Fixes:";
				$tag_space = 0 if ($line =~ /^fixes:? [0-9a-f]{5,} ($balanced_parens)/i);

				$id_length = 0 if ($orig_commit =~ /^[0-9a-f]{12}$/i);
				$id_case = 0 if ($orig_commit !~ /[A-F]/);

				# Always strip leading/trailing parens then double quotes if existing
				$title = substr($title, 1, -1);
				if ($title =~ /^".*"$/) {
					$title = substr($title, 1, -1);
					$title_has_quotes = 1;
				}
			}

			my ($cid, $ctitle) = git_commit_info($orig_commit, $id,
							     $title);

			if ($ctitle ne $title || $tag_case || $tag_space ||
			    $id_length || $id_case || !$title_has_quotes) {
				if (WARN("BAD_FIXES_TAG",
				     "Please use correct Fixes: style 'Fixes: <12 chars of sha1> (\"<title line>\")' - ie: 'Fixes: $cid (\"$ctitle\")'\n" . $herecurr) &&
				    $fix) {
					$fixed[$fixlinenr] = "Fixes: $cid (\"$ctitle\")";
		      $line =~ /^\s*(?:[\w\.\-\+]*\/)++[\w\.\-\+]+:/ ||
		      $line =~ /^\s*(?:Fixes:|$link_tags_search|$signature_tags)/i ||
					# A Fixes:, link or signature tag line
			     "Prefer a maximum 75 chars per line (possible unwrapped commit description?)\n" . $herecurr);
# Check for odd tags before a URI/URL
		if ($in_commit_log &&
		    $line =~ /^\s*(\w+:)\s*http/ && $1 !~ /^$link_tags_search$/) {
			if ($1 =~ /^v(?:ersion)?\d+/i) {
				WARN("COMMIT_LOG_VERSIONING",
				     "Patch version information should be after the --- line\n" . $herecurr);
			} else {
				WARN("COMMIT_LOG_USE_LINK",
				     "Unknown link reference '$1', use $link_tags_print instead\n" . $herecurr);
			}
		}

# Check for misuse of the link tags
		if ($in_commit_log &&
		    $line =~ /^\s*(\w+:)\s*(\S+)/) {
			my $tag = $1;
			my $value = $2;
			if ($tag =~ /^$link_tags_search$/ && $value !~ m{^https?://}) {
				WARN("COMMIT_LOG_WRONG_LINK",
				     "'$tag' should be followed by a public http(s) link\n" . $herecurr);
			}
		}

# Check for mailing list archives other than lore.kernel.org
		if ($rawline =~ m{http.*\b$obsolete_archives}) {
			WARN("PREFER_LORE_ARCHIVE",
			     "Use lore.kernel.org archive links when possible - see https://lore.kernel.org/lists.html\n" . $herecurr);
		}

			my $ln = $linenr;
			my $needs_help = 0;
			my $has_help = 0;
			my $help_length = 0;
			while (defined $lines[$ln]) {
				my $f = $lines[$ln++];
				last if ($f !~ /^[\+ ]/);	# !patch context
				if ($f =~ /^\+\s*(?:bool|tristate|prompt)\s*["']/) {
					$needs_help = 1;
					next;
				}
				if ($f =~ /^\+\s*help\s*$/) {
					$has_help = 1;
					next;
				$f =~ s/^.//;	# strip patch context [+ ]
				$f =~ s/#.*//;	# strip # directives
				$f =~ s/^\s+//;	# strip leading blanks
				next if ($f =~ /^$/);	# skip blank lines
				# At the end of this Kconfig block:
				if ($f =~ /^(?:config|menuconfig|choice|endchoice|
					       if|endif|menu|endmenu|source)\b/x) {
				$help_length++ if ($has_help);
			if ($needs_help &&
			    $help_length < $min_conf_desc_length) {
				my $stat_real = get_stat_real($linenr, $ln - 1);
				     "please write a help paragraph that fully describes the config symbol\n" . "$here\n$stat_real\n");
				} elsif ($realfile =~ /\.(c|rs|dts|dtsi)$/) {
					    $spdx_license !~ /GPL-2\.0(?:-only)? OR BSD-2-Clause/) {
					if ($realfile =~ m@^include/dt-bindings/@ &&
					    $spdx_license !~ /GPL-2\.0(?:-only)? OR \S+/) {
						WARN("SPDX_LICENSE_TAG",
						     "DT binding headers should be licensed (GPL-2.0-only OR .*)\n" . $herecurr);
					}
		if ($rawline =~ /^\+.*\b\Q$realfile\E\b/) {
		next if ($realfile !~ /\.(h|c|rs|s|S|sh|dtsi|dts)$/);
			    show_type("LONG_LINE") && show_type($msg_type)) {
			     "Avoid using '.L' prefixed local symbol names for denoting a range of code via 'SYM_*_START/END' annotations; see Documentation/core-api/asm-annotations.rst\n" . $herecurr);
		      $line =~ /^\+\s*(?:EXPORT_SYMBOL|early_param|ALLOW_ERROR_INJECTION)/ ||
# do not use BUG() or variants
		if ($line =~ /\b(?!AA_|BUILD_|DCCP_|IDA_|KVM_|RWLOCK_|snd_|SPIN_)(?:[a-zA-Z_]*_)?BUG(?:_ON)?(?:_[A-Z_]+)?\s*\(/) {
				      "Do not crash the kernel unless it is absolutely unavoidable--use WARN_ON_ONCE() plus recovery code (if feasible) instead of BUG() or variants\n" . $herecurr);
				asm|__asm__|scoped_guard)$/x)
			my $fixed_assign_in_if = 0;
						$fixed_assign_in_if = 1;
				if (ERROR("TRAILING_STATEMENTS",
					  "trailing statements should be on next line\n" . $herecurr . $stat_real) &&
				    !$fixed_assign_in_if &&
				    $cond_lines == 0 &&
				    $fix && $perl_version_ok &&
				    $fixed[$fixlinenr] =~ /^\+(\s*)((?:if|while|for)\s*$balanced_parens)\s*(.*)$/) {
					my $indent = $1;
					my $test = $2;
					my $rest = rtrim($4);
					if ($rest =~ /;$/) {
						$fixed[$fixlinenr] = "\+$indent$test";
						fix_insert_line($fixlinenr + 1, "$indent\t$rest");
					}
				}
#Ignore ETHTOOL_LINK_MODE_<foo> variants
			    $var !~ /^ETHTOOL_LINK_MODE_/ &&
				while ($var =~ m{\b($Ident)}g) {
			    $dstat !~ /^case\b/ &&					# case ...

# check if this is an unused argument
				if ($define_stmt !~ /\b$arg\b/) {
					WARN("MACRO_ARG_UNUSED",
					     "Argument '$arg' is not used in function-like macro\n" . "$herectx");
				}
		} elsif ($realfile =~ m@/vmlinux.lds.h$@) {
		    $line =~ s/(\w+)/$maybe_linker_symbol{$1}++/ge;
		    #print "REAL: $realfile\nln: $line\nkeys:", sort keys %maybe_linker_symbol;
					my $msg_level = \&WARN;
					} elsif ($bad_specifier =~ /pA/) {
						$use =  " - '%pA' is only intended to be used from Rust code";
						$msg_level = \&ERROR;
					&{$msg_level}("VSPRINTF_POINTER_EXTENSION",
						      "$ext_type vsprintf pointer extension '$bad_specifier'$use\n" . "$here\n$stat_real\n");
# strcpy uses that should likely be strscpy
		if ($line =~ /\bstrcpy\s*\(/) {
			WARN("STRCPY",
			     "Prefer strscpy over strcpy - see: https://github.com/KSPP/linux/issues/88\n" . $herecurr);
		}

			     "Prefer strscpy over strlcpy - see: https://github.com/KSPP/linux/issues/89\n" . $herecurr);
		}

# strncpy uses that should likely be strscpy or strscpy_pad
		if ($line =~ /\bstrncpy\s*\(/) {
			WARN("STRNCPY",
			     "Prefer strscpy, strscpy_pad, or __nonstring over strncpy - see: https://github.com/KSPP/linux/issues/90\n" . $herecurr);
		}

# ethtool_sprintf uses that should likely be ethtool_puts
		if ($line =~ /\bethtool_sprintf\s*\(\s*$FuncArg\s*,\s*$FuncArg\s*\)/) {
			if (WARN("PREFER_ETHTOOL_PUTS",
				 "Prefer ethtool_puts over ethtool_sprintf with only two arguments\n" . $herecurr) &&
			    $fix) {
				$fixed[$fixlinenr] =~ s/\bethtool_sprintf\s*\(\s*($FuncArg)\s*,\s*($FuncArg)/ethtool_puts($1, $7)/;
			}
		}

		# use $rawline because $line loses %s via sanitization and thus we can't match against it.
		if ($rawline =~ /\bethtool_sprintf\s*\(\s*$FuncArg\s*,\s*\"\%s\"\s*,\s*$FuncArg\s*\)/) {
			if (WARN("PREFER_ETHTOOL_PUTS",
				 "Prefer ethtool_puts over ethtool_sprintf with standalone \"%s\" specifier\n" . $herecurr) &&
			    $fix) {
				$fixed[$fixlinenr] =~ s/\bethtool_sprintf\s*\(\s*($FuncArg)\s*,\s*"\%s"\s*,\s*($FuncArg)/ethtool_puts($1, $7)/;
			}

		} elsif ($realfile =~ /\.c$/ && defined $stat &&
		    $stat =~ /^\+extern struct\s+(\w+)\s+(\w+)\[\];/)
		{
			my ($st_type, $st_name) = ($1, $2);

			for my $s (keys %maybe_linker_symbol) {
			    #print "Linker symbol? $st_name : $s\n";
			    goto LIKELY_LINKER_SYMBOL
				if $st_name =~ /$s/;
			}
			WARN("AVOID_EXTERNS",
			     "found a file-scoped extern type:$st_type name:$st_name in .c file\n"
			     . "is this a linker symbol ?\n" . $herecurr);
		  LIKELY_LINKER_SYMBOL:

# check for (kv|k)[mz]alloc with multiplies that could be kmalloc_array/kvmalloc_array/kvcalloc/kcalloc
		    $stat =~ /^\+\s*($Lval)\s*\=\s*(?:$balanced_parens)?\s*((?:kv|k)[mz]alloc)\s*\(\s*($FuncArg)\s*\*\s*($FuncArg)\s*,/) {
			$newfunc = "kvmalloc_array" if ($oldfunc eq "kvmalloc");
			$newfunc = "kvcalloc" if ($oldfunc eq "kvzalloc");
					$fixed[$fixlinenr] =~ s/\b($Lval)\s*\=\s*(?:$balanced_parens)?\s*((?:kv|k)[mz]alloc)\s*\(\s*($FuncArg)\s*\*\s*($FuncArg)/$1 . ' = ' . "$newfunc(" . trim($r1) . ', ' . trim($r2)/e;
		if ($line =~ /\b((?:devm_)?((?:k|kv)?(calloc|malloc_array)(?:_node)?))\s*\(\s*sizeof\b/) {
# check for array definition/declarations that should use flexible arrays instead
		if ($sline =~ /^[\+ ]\s*\}(?:\s*__packed)?\s*;\s*$/ &&
		    $prevline =~ /^\+\s*(?:\}(?:\s*__packed\s*)?|$Type)\s*$Ident\s*\[\s*(0|1)\s*\]\s*;\s*$/) {
			if (ERROR("FLEXIBLE_ARRAY",
				  "Use C99 flexible arrays - see https://docs.kernel.org/process/deprecated.html#zero-length-and-one-element-arrays\n" . $hereprev) &&
			    $1 == '0' && $fix) {
				$fixed[$fixlinenr - 1] =~ s/\[\s*0\s*\]/[]/;
			}
		}

# Complain about RCU Tasks Trace used outside of BPF (and of course, RCU).
		our $rcu_trace_funcs = qr{(?x:
			rcu_read_lock_trace |
			rcu_read_lock_trace_held |
			rcu_read_unlock_trace |
			call_rcu_tasks_trace |
			synchronize_rcu_tasks_trace |
			rcu_barrier_tasks_trace |
			rcu_request_urgent_qs_task
		)};
		our $rcu_trace_paths = qr{(?x:
			kernel/bpf/ |
			include/linux/bpf |
			net/bpf/ |
			kernel/rcu/ |
			include/linux/rcu
		)};
		if ($line =~ /\b($rcu_trace_funcs)\s*\(/) {
			if ($realfile !~ m{^$rcu_trace_paths}) {
				WARN("RCU_TASKS_TRACE",
				     "use of RCU tasks trace is incorrect outside BPF or core RCU code\n" . $herecurr);
			}
		}

			if (!$file && $extracted_string eq '"GPL v2"') {
				if (WARN("MODULE_LICENSE",
				     "Prefer \"GPL\" over \"GPL v2\" - see commit bf7fbeeae6db (\"module: Cure the MODULE_LICENSE \"GPL\" vs. \"GPL v2\" bogosity\")\n" . $herecurr) &&
				    $fix) {
					$fixed[$fixlinenr] =~ s/\bMODULE_LICENSE\s*\(\s*"GPL v2"\s*\)/MODULE_LICENSE("GPL")/;
				}
			}
	if ($is_patch && $has_commit_log && $chk_fixes_tag) {
		if ($needs_fixes_tag ne "" && !$is_revert && !$fixes_tag) {
			WARN("MISSING_FIXES_TAG",
				 "The commit message has '$needs_fixes_tag', perhaps it also needs a 'Fixes:' tag?\n");
		}
	}