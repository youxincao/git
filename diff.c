#include "userdiff.h"
static int diff_suppress_blank_empty;
static int diff_mnemonic_prefix;
static void diff_filespec_load_driver(struct diff_filespec *one);
static char *run_textconv(const char *, struct diff_filespec *, size_t *);

	if (!strcmp(var, "diff.mnemonicprefix")) {
		diff_mnemonic_prefix = git_config_bool(var, value);
		return 0;
	}
	switch (userdiff_config(var, value)) {
		case 0: break;
		case -1: return -1;
		default: return 0;
	}

	/* like GNU diff's --suppress-blank-empty option  */
	if (!strcmp(var, "diff.suppress-blank-empty")) {
		diff_suppress_blank_empty = git_config_bool(var, value);
		return 0;
	struct strbuf res = STRBUF_INIT;
			      const char *textconv_one,
			      const char *textconv_two,
	const char *a_prefix, *b_prefix;
	const char *data_one, *data_two;
	size_t size_one, size_two;

	if (diff_mnemonic_prefix && DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}
	quote_two_c_style(&a_name, a_prefix, name_a, 0);
	quote_two_c_style(&b_name, b_prefix, name_b, 0);
	if (textconv_one) {
		data_one = run_textconv(textconv_one, one, &size_one);
		if (!data_one)
			die("unable to read files to diff");
	}
	else {
		data_one = one->data;
		size_one = one->size;
	}
	if (textconv_two) {
		data_two = run_textconv(textconv_two, two, &size_two);
		if (!data_two)
			die("unable to read files to diff");
	}
	else {
		data_two = two->data;
		size_two = two->size;
	}

	lc_a = count_lines(data_one, size_one);
	lc_b = count_lines(data_two, size_two);
		copy_file_with_prefix(o->file, '-', data_one, size_one, old, reset);
		copy_file_with_prefix(o->file, '+', data_two, size_two, new, reset);

	memset(&xpp, 0, sizeof(xpp));
	xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, diff_words,
		      &xpp, &xecfg, &ecb);
	if (diff_suppress_blank_empty
	    && len == 2 && line[0] == ' ' && line[1] == '\n') {
		line[0] = '\n';
		len = 1;
	}

	struct strbuf name = STRBUF_INIT;
		struct strbuf buf = STRBUF_INIT;
		 * made to the preimage. In --dirstat-by-file mode, count
		 * damaged files, not damaged lines. This is done by
		 * counting only a single damaged line per file.
		if (DIFF_OPT_TST(options, DIRSTAT_BY_FILE) && damage > 0)
			damage = 1;
static void diff_filespec_load_driver(struct diff_filespec *one)
	if (!one->driver)
		one->driver = userdiff_find_by_path(one->path);
	if (!one->driver)
		one->driver = userdiff_find_by_name("default");
int diff_filespec_is_binary(struct diff_filespec *one)
	if (one->is_binary == -1) {
		diff_filespec_load_driver(one);
		if (one->driver->binary != -1)
			one->is_binary = one->driver->binary;
		else {
			if (!one->data && DIFF_FILE_VALID(one))
				diff_populate_filespec(one, 0);
			if (one->data)
				one->is_binary = buffer_is_binary(one->data,
						one->size);
			if (one->is_binary == -1)
				one->is_binary = 0;
		}
	return one->is_binary;
static const struct userdiff_funcname *diff_funcname_pattern(struct diff_filespec *one)
	diff_filespec_load_driver(one);
	return one->driver->funcname.pattern ? &one->driver->funcname : NULL;
void diff_set_mnemonic_prefix(struct diff_options *options, const char *a, const char *b)
	if (!options->a_prefix)
		options->a_prefix = a;
	if (!options->b_prefix)
		options->b_prefix = b;
}
static const char *get_textconv(struct diff_filespec *one)
{
	if (!DIFF_FILE_VALID(one))
		return NULL;
	if (!S_ISREG(one->mode))
		return NULL;
	diff_filespec_load_driver(one);
	return one->driver->textconv;
	const char *a_prefix, *b_prefix;
	const char *textconv_one = NULL, *textconv_two = NULL;

	if (DIFF_OPT_TST(o, ALLOW_TEXTCONV)) {
		textconv_one = get_textconv(one);
		textconv_two = get_textconv(two);
	}

	diff_set_mnemonic_prefix(o, "a/", "b/");
	if (DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}
	a_one = quote_two(a_prefix, name_a + (*name_a == '/'));
	b_two = quote_two(b_prefix, name_b + (*name_b == '/'));
		if (complete_rewrite &&
		    (textconv_one || !diff_filespec_is_binary(one)) &&
		    (textconv_two || !diff_filespec_is_binary(two))) {
			emit_rewrite_diff(name_a, name_b, one, two,
						textconv_one, textconv_two, o);
	    ( (diff_filespec_is_binary(one) && !textconv_one) ||
	      (diff_filespec_is_binary(two) && !textconv_two) )) {
		const struct userdiff_funcname *pe;

		if (textconv_one) {
			size_t size;
			mf1.ptr = run_textconv(textconv_one, one, &size);
			if (!mf1.ptr)
				die("unable to read files to diff");
			mf1.size = size;
		}
		if (textconv_two) {
			size_t size;
			mf2.ptr = run_textconv(textconv_two, two, &size);
			if (!mf2.ptr)
				die("unable to read files to diff");
			mf2.size = size;
		}
		memset(&xpp, 0, sizeof(xpp));
		xecfg.interhunkctxlen = o->interhunkcontext;
		xdi_diff_outf(&mf1, &mf2, fn_out_consume, &ecbdata,
			      &xpp, &xecfg, &ecb);
		if (textconv_one)
			free(mf1.ptr);
		if (textconv_two)
			free(mf2.ptr);
		memset(&xpp, 0, sizeof(xpp));
		xdi_diff_outf(&mf1, &mf2, diffstat_consume, diffstat,
			      &xpp, &xecfg, &ecb);
		memset(&xpp, 0, sizeof(xpp));
		xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
			      &xpp, &xecfg, &ecb);
	spec->is_binary = -1;
	struct strbuf buf = STRBUF_INIT;
		struct strbuf buf = STRBUF_INIT;
			struct strbuf sb = STRBUF_INIT;

			if (strbuf_readlink(&sb, s->path, s->size))
			s->size = sb.len;
			s->data = strbuf_detach(&sb, NULL);
			s->should_free = 1;
		if (size_only)
			return 0;
			ret = readlink(name, buf, sizeof(buf));
			if (ret == sizeof(buf))
				die("symlink too long: %s", name);
			prep_temp_blob(temp, buf, ret,
		struct userdiff_driver *drv = userdiff_find_by_path(attr_path);
		if (drv && drv->external)
			pgm = drv->external;
				die("cannot hash %s", one->path);
	if (!diff_mnemonic_prefix) {
		options->a_prefix = "a/";
		options->b_prefix = "b/";
	}
	} else if (opt_arg(arg, 0, "dirstat-by-file",
			   &options->dirstat_percent)) {
		options->output_format |= DIFF_FORMAT_DIRSTAT;
		DIFF_OPT_SET(options, DIRSTAT_BY_FILE);
	else if (!strcmp(arg, "--textconv"))
		DIFF_OPT_SET(options, ALLOW_TEXTCONV);
	else if (!strcmp(arg, "--no-textconv"))
		DIFF_OPT_CLR(options, ALLOW_TEXTCONV);
	else if (opt_arg(arg, '\0', "inter-hunk-context",
			 &options->interhunkcontext))
		;
	git_SHA_CTX *ctx;
	git_SHA1_Update(data->ctx, line, new_len);
	git_SHA_CTX ctx;
	git_SHA1_Init(&ctx);
		memset(&xpp, 0, sizeof(xpp));
		git_SHA1_Update(&ctx, buffer, len1);
		xdi_diff_outf(&mf1, &mf2, patch_id_consume, &data,
			      &xpp, &xecfg, &ecb);
	git_SHA1_Final(sha1, &ctx);

static char *run_textconv(const char *pgm, struct diff_filespec *spec,
		size_t *outsize)
{
	struct diff_tempfile temp;
	const char *argv[3];
	const char **arg = argv;
	struct child_process child;
	struct strbuf buf = STRBUF_INIT;

	prepare_temp_file(spec->path, &temp, spec);
	*arg++ = pgm;
	*arg++ = temp.name;
	*arg = NULL;

	memset(&child, 0, sizeof(child));
	child.argv = argv;
	child.out = -1;
	if (start_command(&child) != 0 ||
	    strbuf_read(&buf, child.out, 0) < 0 ||
	    finish_command(&child) != 0) {
		if (temp.name == temp.tmp_path)
			unlink(temp.name);
		error("error running textconv command '%s'", pgm);
		return NULL;
	}
	if (temp.name == temp.tmp_path)
		unlink(temp.name);

	return strbuf_detach(&buf, outsize);
}