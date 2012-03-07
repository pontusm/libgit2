	if ((delta->old.flags & GIT_DIFF_FILE_BINARY) != 0 ||
		(delta->new.flags & GIT_DIFF_FILE_BINARY) != 0)
	else if ((delta->old.flags & GIT_DIFF_FILE_NOT_BINARY) != 0 ||
			 (delta->new.flags & GIT_DIFF_FILE_NOT_BINARY) != 0)
	if ((git_off_t)((size_t)delta->old.size) != delta->old.size ||
		(git_off_t)((size_t)delta->new.size) != delta->new.size)
		delta->old.flags |= GIT_DIFF_FILE_BINARY;
		delta->new.flags |= GIT_DIFF_FILE_BINARY;
		delta->old.flags |= GIT_DIFF_FILE_NOT_BINARY;
		delta->new.flags |= GIT_DIFF_FILE_NOT_BINARY;
	error = set_file_is_binary_by_attr(diff->repo, &delta->old);
	mirror_new = (delta->new.path == delta->old.path ||
				  strcmp(delta->new.path, delta->old.path) == 0);
		delta->new.flags &= (delta->old.flags & BINARY_DIFF_FLAGS);
		error = set_file_is_binary_by_attr(diff->repo, &delta->new);
	if ((delta->old.flags & BINARY_DIFF_FLAGS) == 0) {
		size_t search_len = min(old_data->len, 4000);
		if (strnlen(old_data->data, search_len) != search_len)
			delta->old.flags |= GIT_DIFF_FILE_BINARY;
			delta->old.flags |= GIT_DIFF_FILE_NOT_BINARY;
	if ((delta->new.flags & BINARY_DIFF_FLAGS) == 0) {
		size_t search_len = min(new_data->len, 4000);
		if (strnlen(new_data->data, search_len) != search_len)
			delta->new.flags |= GIT_DIFF_FILE_BINARY;
			delta->new.flags |= GIT_DIFF_FILE_NOT_BINARY;
				error = get_workdir_content(diff->repo, &delta->old, &old_data);
					diff->repo, &delta->old.oid, &old_data, &old_blob);
			(hunk_cb || line_cb || git_oid_iszero(&delta->new.oid)) &&
				error = get_workdir_content(diff->repo, &delta->new, &new_data);
					diff->repo, &delta->new.oid, &new_data, &new_blob);
			if ((delta->new.flags | GIT_DIFF_FILE_VALID_OID) == 0) {
					&delta->new.oid, new_data.data, new_data.len, GIT_OBJ_BLOB);
				if (git_oid_cmp(&delta->old.oid, &delta->new.oid) == 0) {
		xdl_diff((mmfile_t *)&old_data, (mmfile_t *)&new_data,
		release_content(&delta->old, &old_data, old_blob);
		release_content(&delta->new, &new_data, new_blob);
	old_suffix = pick_suffix(delta->old.mode);
	new_suffix = pick_suffix(delta->new.mode);
	if (delta->old.path != delta->new.path &&
		strcmp(delta->old.path,delta->new.path) != 0)
			delta->old.path, old_suffix, delta->new.path, new_suffix);
	else if (delta->old.mode != delta->new.mode &&
		delta->old.mode != 0 && delta->new.mode != 0)
			delta->old.path, new_suffix, delta->old.mode, delta->new.mode);
		git_buf_printf(pi->buf, "%c\t%s%c\n", code, delta->old.path, old_suffix);
		git_buf_printf(pi->buf, "%c\t%s\n", code, delta->old.path);
	if (git_buf_oom(pi->buf) == true)
		return GIT_ENOMEM;
	git_oid_to_string(start_oid, sizeof(start_oid), &delta->old.oid);
	git_oid_to_string(end_oid, sizeof(end_oid), &delta->new.oid);
	if (delta->old.mode == delta->new.mode) {
			start_oid, end_oid, delta->old.mode);
		if (delta->old.mode == 0) {
			git_buf_printf(pi->buf, "new file mode %o\n", delta->new.mode);
		} else if (delta->new.mode == 0) {
			git_buf_printf(pi->buf, "deleted file mode %o\n", delta->old.mode);
			git_buf_printf(pi->buf, "old mode %o\n", delta->old.mode);
			git_buf_printf(pi->buf, "new mode %o\n", delta->new.mode);
	if (git_buf_oom(pi->buf))
		return GIT_ENOMEM;

	return 0;
	const char *oldpfx = pi->diff->opts.src_prefix;
	const char *oldpath = delta->old.path;
	const char *newpfx = pi->diff->opts.dst_prefix;
	const char *newpath = delta->new.path;
	git_buf_printf(pi->buf, "diff --git %s%s %s%s\n", oldpfx, delta->old.path, newpfx, delta->new.path);
	if (git_oid_iszero(&delta->old.oid)) {
	if (git_oid_iszero(&delta->new.oid)) {
	if (git_buf_oom(pi->buf))
		return GIT_ENOMEM;
	if (git_buf_oom(pi->buf))
		return GIT_ENOMEM;
		return GIT_ENOMEM;
	if (git_buf_oom(pi->buf))
		return GIT_ENOMEM;
	mmfile_t old, new;
		old.ptr  = (char *)git_blob_rawcontent(old_blob);
		old.size = git_blob_rawsize(old_blob);
		old.ptr  = "";
		old.size = 0;
		new.ptr  = (char *)git_blob_rawcontent(new_blob);
		new.size = git_blob_rawsize(new_blob);
		new.ptr  = "";
		new.size = 0;
	delta.status = old.ptr ?
		(new.ptr ? GIT_DELTA_MODIFIED : GIT_DELTA_DELETED) :
		(new.ptr ? GIT_DELTA_ADDED : GIT_DELTA_UNTRACKED);
	delta.old.mode = 0100644; /* can't know the truth from a blob alone */
	delta.new.mode = 0100644;
	git_oid_cpy(&delta.old.oid, git_object_id((const git_object *)old_blob));
	git_oid_cpy(&delta.new.oid, git_object_id((const git_object *)new_blob));
	delta.old.path = NULL;
	delta.new.path = NULL;
	xdl_diff(&old, &new, &xdiff_params, &xdiff_config, &xdiff_callback);