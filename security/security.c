#include <linux/integrity.h>
#include <linux/ima.h>
#include <linux/evm.h>
#define MAX_LSM_EVM_XATTR	2
/* How many LSMs were built into the kernel? */
#define LSM_COUNT (__end_lsm_info - __start_lsm_info)
const char *const lockdown_reasons[LOCKDOWN_CONFIDENTIALITY_MAX+1] = {
struct security_hook_heads security_hook_heads __lsm_ro_after_init;
static struct lsm_blob_sizes blob_sizes __lsm_ro_after_init;
static __initconst const char * const builtin_lsm_order = CONFIG_LSM;
static __initdata struct lsm_info **ordered_lsms;
	if (WARN(last_lsm == LSM_COUNT, "%s: out of LSM slots!?\n", from))
	init_debug("%s ordering: %s (%sabled)\n", from, lsm->name,
		   is_enabled(lsm) ? "en" : "dis");
	if (*need > 0) {
		offset = *lbs;
		*lbs += *need;
		*need = offset;
	}
			init_debug("exclusive chosen: %s\n", lsm->name);
			append_ordered_lsm(lsm, "first");
				init_debug("security=%s disabled: %s\n",
			if (lsm->order == LSM_ORDER_MUTABLE &&
			    strcmp(lsm->name, name) == 0) {
				append_ordered_lsm(lsm, origin);
			init_debug("%s ignored: %s\n", origin, name);
		init_debug("%s disabled: %s\n", origin, lsm->name);
	ordered_lsms = kcalloc(LSM_COUNT + 1, sizeof(*ordered_lsms),
				GFP_KERNEL);

			pr_info("security= is ignored because it is superseded by lsm=\n");

	kfree(ordered_lsms);
	int i;
	struct hlist_head *list = (struct hlist_head *) &security_hook_heads;
	for (i = 0; i < sizeof(security_hook_heads) / sizeof(struct hlist_head);
	     i++)
		INIT_HLIST_HEAD(&list[i]);

	pr_info("Security Framework initializing\n");
 * @lsm: the name of the security module
				char *lsm)
		hooks[i].lsm = lsm;
		hlist_add_tail_rcu(&hooks[i].list, hooks[i].head);
		if (lsm_append(lsm, &lsm_names) < 0)
 * lsm_cred_alloc - allocate a composite cred blob
 * @cred: the cred that needs a blob
 * Allocate the cred blob for all the modules
static int lsm_cred_alloc(struct cred *cred, gfp_t gfp)
	if (blob_sizes.lbs_cred == 0) {
		cred->security = NULL;
	cred->security = kzalloc(blob_sizes.lbs_cred, gfp);
	if (cred->security == NULL)
int lsm_inode_alloc(struct inode *inode)
	inode->i_security = kmem_cache_zalloc(lsm_inode_cache, GFP_NOFS);
	if (blob_sizes.lbs_task == 0) {
		task->security = NULL;
		return 0;
	}

	task->security = kzalloc(blob_sizes.lbs_task, GFP_KERNEL);
	if (task->security == NULL)
		return -ENOMEM;
	return 0;
	if (blob_sizes.lbs_ipc == 0) {
		kip->security = NULL;
		return 0;
	}
	kip->security = kzalloc(blob_sizes.lbs_ipc, GFP_KERNEL);
	if (kip->security == NULL)
		return -ENOMEM;
	return 0;
	if (blob_sizes.lbs_msg_msg == 0) {
		mp->security = NULL;
	mp->security = kzalloc(blob_sizes.lbs_msg_msg, GFP_KERNEL);
	if (mp->security == NULL)
	if (blob_sizes.lbs_superblock == 0) {
		sb->s_security = NULL;
		return 0;
	sb->s_security = kzalloc(blob_sizes.lbs_superblock, GFP_KERNEL);
	if (sb->s_security == NULL)
		return -ENOMEM;
	return 0;
#define call_void_hook(FUNC, ...)				\
	do {							\
		struct security_hook_list *P;			\
								\
		hlist_for_each_entry(P, &security_hook_heads.FUNC, list) \
			P->hook.FUNC(__VA_ARGS__);		\
	} while (0)
#define call_int_hook(FUNC, IRC, ...) ({			\
	int RC = IRC;						\
	do {							\
		struct security_hook_list *P;			\
								\
		hlist_for_each_entry(P, &security_hook_heads.FUNC, list) { \
			RC = P->hook.FUNC(__VA_ARGS__);		\
			if (RC != 0)				\
				break;				\
		}						\
	} while (0);						\
	RC;							\
	return call_int_hook(binder_set_context_mgr, 0, mgr);
	return call_int_hook(binder_transaction, 0, from, to);
	return call_int_hook(binder_transfer_binder, 0, from, to);
				  const struct cred *to, struct file *file)
	return call_int_hook(binder_transfer_file, 0, from, to, file);
	return call_int_hook(ptrace_access_check, 0, child, mode);
	return call_int_hook(ptrace_traceme, 0, parent);
int security_capget(struct task_struct *target,
		     kernel_cap_t *effective,
		     kernel_cap_t *inheritable,
		     kernel_cap_t *permitted)
	return call_int_hook(capget, 0, target,
				effective, inheritable, permitted);
	return call_int_hook(capset, 0, new, old,
				effective, inheritable, permitted);
	return call_int_hook(capable, 0, cred, ns, cap, opts);
int security_quotactl(int cmds, int type, int id, struct super_block *sb)
	return call_int_hook(quotactl, 0, cmds, type, id, sb);
	return call_int_hook(quota_on, 0, dentry);
	return call_int_hook(syslog, 0, type);
	return call_int_hook(settime, 0, ts, tz);
	struct security_hook_list *hp;
	 * The module will respond with a positive value if
	 * it thinks the __vm_enough_memory() call should be
	 * made with the cap_sys_admin set. If all of the modules
	 * agree that it should be set it will. If any module
	 * thinks it should not be set it won't.
	hlist_for_each_entry(hp, &security_hook_heads.vm_enough_memory, list) {
		rc = hp->hook.vm_enough_memory(mm, pages);
		if (rc <= 0) {
	return call_int_hook(bprm_creds_for_exec, 0, bprm);
int security_bprm_creds_from_file(struct linux_binprm *bprm, struct file *file)
	return call_int_hook(bprm_creds_from_file, 0, bprm, file);
	int ret;

	ret = call_int_hook(bprm_check_security, 0, bprm);
	if (ret)
		return ret;
	return ima_bprm_check(bprm);
void security_bprm_committing_creds(struct linux_binprm *bprm)
void security_bprm_committed_creds(struct linux_binprm *bprm)
	return call_int_hook(fs_context_dup, 0, fc, src_fc);
int security_fs_context_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	return call_int_hook(fs_context_parse_param, -ENOPARAM, fc, param);
	rc = call_int_hook(sb_alloc_security, 0, sb);
	return call_int_hook(sb_eat_lsm_opts, 0, options, mnt_opts);
	return call_int_hook(sb_mnt_opts_compat, 0, sb, mnt_opts);
	return call_int_hook(sb_remount, 0, sb, mnt_opts);
int security_sb_kern_mount(struct super_block *sb)
	return call_int_hook(sb_kern_mount, 0, sb);
	return call_int_hook(sb_show_options, 0, m, sb);
	return call_int_hook(sb_statfs, 0, dentry);
                       const char *type, unsigned long flags, void *data)
	return call_int_hook(sb_mount, 0, dev_name, path, type, flags, data);
	return call_int_hook(sb_umount, 0, mnt, flags);
int security_sb_pivotroot(const struct path *old_path, const struct path *new_path)
	return call_int_hook(sb_pivotroot, 0, old_path, new_path);
				void *mnt_opts,
				unsigned long kern_flags,
				unsigned long *set_kern_flags)
	return call_int_hook(sb_set_mnt_opts,
				mnt_opts ? -EOPNOTSUPP : 0, sb,
				mnt_opts, kern_flags, set_kern_flags);
				struct super_block *newsb,
				unsigned long kern_flags,
				unsigned long *set_kern_flags)
	return call_int_hook(sb_clone_mnt_opts, 0, oldsb, newsb,
				kern_flags, set_kern_flags);
int security_add_mnt_opt(const char *option, const char *val, int len,
			 void **mnt_opts)
	return call_int_hook(sb_add_mnt_opt, -EINVAL,
					option, val, len, mnt_opts);
}
EXPORT_SYMBOL(security_add_mnt_opt);

int security_move_mount(const struct path *from_path, const struct path *to_path)
{
	return call_int_hook(move_mount, 0, from_path, to_path);
				unsigned int obj_type)
	return call_int_hook(path_notify, 0, path, mask, obj_type);
int security_inode_alloc(struct inode *inode)
	int rc = lsm_inode_alloc(inode);
	rc = call_int_hook(inode_alloc_security, 0, inode);
	/*
	 * The rcu head is at the start of the inode blob
	 */
	integrity_inode_free(inode);
	/*
	 * The inode may still be referenced in a path walk and
	 * a call to security_inode_permission() can be made
	 * after inode_free_security() is called. Ideally, the VFS
	 * wouldn't do this, but fixing that is a much harder
	 * job. For now, simply free the i_security via RCU, and
	 * leave the current inode->i_security pointer intact.
	 * The inode will be freed after the RCU grace period too.
	 */
	if (inode->i_security)
		call_rcu((struct rcu_head *)inode->i_security,
				inode_free_by_rcu);
	struct security_hook_list *hp;
	int rc;

	/*
	 * Only one module will provide a security context.
	 */
	hlist_for_each_entry(hp, &security_hook_heads.dentry_init_security, list) {
		rc = hp->hook.dentry_init_security(dentry, mode, name,
						   xattr_name, ctx, ctxlen);
		if (rc != LSM_RET_DEFAULT(dentry_init_security))
			return rc;
	}
	return LSM_RET_DEFAULT(dentry_init_security);
	return call_int_hook(dentry_create_files_as, 0, dentry, mode,
				name, old, new);
	struct xattr new_xattrs[MAX_LSM_EVM_XATTR + 1];
	struct xattr *lsm_xattr, *evm_xattr, *xattr;
	int ret;
	if (!initxattrs)
		return call_int_hook(inode_init_security, -EOPNOTSUPP, inode,
				     dir, qstr, NULL, NULL, NULL);
	memset(new_xattrs, 0, sizeof(new_xattrs));
	lsm_xattr = new_xattrs;
	ret = call_int_hook(inode_init_security, -EOPNOTSUPP, inode, dir, qstr,
						&lsm_xattr->name,
						&lsm_xattr->value,
						&lsm_xattr->value_len);
	if (ret)
	evm_xattr = lsm_xattr + 1;
	ret = evm_inode_init_security(inode, lsm_xattr, evm_xattr);
	if (ret)
		goto out;
	for (xattr = new_xattrs; xattr->value != NULL; xattr++)
		kfree(xattr->value);
	return call_int_hook(inode_init_security_anon, 0, inode, name,
int security_old_inode_init_security(struct inode *inode, struct inode *dir,
				     const struct qstr *qstr, const char **name,
				     void **value, size_t *len)
{
	if (unlikely(IS_PRIVATE(inode)))
		return -EOPNOTSUPP;
	return call_int_hook(inode_init_security, -EOPNOTSUPP, inode, dir,
			     qstr, name, value, len);
}
EXPORT_SYMBOL(security_old_inode_init_security);

int security_path_mknod(const struct path *dir, struct dentry *dentry, umode_t mode,
			unsigned int dev)
	return call_int_hook(path_mknod, 0, dir, dentry, mode, dev);
int security_path_mkdir(const struct path *dir, struct dentry *dentry, umode_t mode)
	return call_int_hook(path_mkdir, 0, dir, dentry, mode);
	return call_int_hook(path_rmdir, 0, dir, dentry);
EXPORT_SYMBOL_GPL(security_path_rmdir);
	return call_int_hook(path_unlink, 0, dir, dentry);
	return call_int_hook(path_symlink, 0, dir, dentry, old_name);
EXPORT_SYMBOL_GPL(security_path_symlink);
	return call_int_hook(path_link, 0, old_dentry, new_dir, new_dentry);
EXPORT_SYMBOL_GPL(security_path_link);
		     (d_is_positive(new_dentry) && IS_PRIVATE(d_backing_inode(new_dentry)))))
	if (flags & RENAME_EXCHANGE) {
		int err = call_int_hook(path_rename, 0, new_dir, new_dentry,
					old_dir, old_dentry);
		if (err)
			return err;
	}

	return call_int_hook(path_rename, 0, old_dir, old_dentry, new_dir,
				new_dentry);
	return call_int_hook(path_truncate, 0, path);
EXPORT_SYMBOL_GPL(security_path_truncate);
	return call_int_hook(path_chmod, 0, path, mode);
EXPORT_SYMBOL_GPL(security_path_chmod);
	return call_int_hook(path_chown, 0, path, uid, gid);
EXPORT_SYMBOL_GPL(security_path_chown);
	return call_int_hook(path_chroot, 0, path);
#endif
int security_inode_create(struct inode *dir, struct dentry *dentry, umode_t mode)
	return call_int_hook(inode_create, 0, dir, dentry, mode);
			 struct dentry *new_dentry)
	return call_int_hook(inode_link, 0, old_dentry, dir, new_dentry);
	return call_int_hook(inode_unlink, 0, dir, dentry);
			    const char *old_name)
	return call_int_hook(inode_symlink, 0, dir, dentry, old_name);
	return call_int_hook(inode_mkdir, 0, dir, dentry, mode);
	return call_int_hook(inode_rmdir, 0, dir, dentry);
int security_inode_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
	return call_int_hook(inode_mknod, 0, dir, dentry, mode, dev);
			   struct inode *new_dir, struct dentry *new_dentry,
			   unsigned int flags)
        if (unlikely(IS_PRIVATE(d_backing_inode(old_dentry)) ||
            (d_is_positive(new_dentry) && IS_PRIVATE(d_backing_inode(new_dentry)))))
		int err = call_int_hook(inode_rename, 0, new_dir, new_dentry,
						     old_dir, old_dentry);
	return call_int_hook(inode_rename, 0, old_dir, old_dentry,
					   new_dir, new_dentry);
	return call_int_hook(inode_readlink, 0, dentry);
	return call_int_hook(inode_follow_link, 0, dentry, inode, rcu);
	return call_int_hook(inode_permission, 0, inode, mask);
EXPORT_SYMBOL_GPL(security_inode_permission);
int security_inode_setattr(struct dentry *dentry, struct iattr *attr)
	int ret;

	ret = call_int_hook(inode_setattr, 0, dentry, attr);
	if (ret)
		return ret;
	return evm_inode_setattr(dentry, attr);
	return call_int_hook(inode_getattr, 0, path);
int security_inode_setxattr(struct user_namespace *mnt_userns,
	int ret;
	/*
	 * SELinux and Smack integrate the cap call,
	 * so assume that all LSMs supplying this call do so.
	 */
	ret = call_int_hook(inode_setxattr, 1, mnt_userns, dentry, name, value,
			    size, flags);
	if (ret == 1)
		ret = cap_inode_setxattr(dentry, name, value, size, flags);
	if (ret)
		return ret;
	ret = ima_inode_setxattr(dentry, name, value, size);
	if (ret)
		return ret;
	return evm_inode_setxattr(mnt_userns, dentry, name, value, size);
void security_inode_post_setxattr(struct dentry *dentry, const char *name,
				  const void *value, size_t size, int flags)
		return;
	call_void_hook(inode_post_setxattr, dentry, name, value, size, flags);
	evm_inode_post_setxattr(dentry, name, value, size);
int security_inode_getxattr(struct dentry *dentry, const char *name)
		return 0;
	return call_int_hook(inode_getxattr, 0, dentry, name);
int security_inode_listxattr(struct dentry *dentry)
	return call_int_hook(inode_listxattr, 0, dentry);
int security_inode_removexattr(struct user_namespace *mnt_userns,
	int ret;
	/*
	 * SELinux and Smack integrate the cap call,
	 * so assume that all LSMs supplying this call do so.
	 */
	ret = call_int_hook(inode_removexattr, 1, mnt_userns, dentry, name);
	if (ret == 1)
		ret = cap_inode_removexattr(mnt_userns, dentry, name);
	if (ret)
		return ret;
	ret = ima_inode_removexattr(dentry, name);
	if (ret)
		return ret;
	return evm_inode_removexattr(mnt_userns, dentry, name);
	return call_int_hook(inode_need_killpriv, 0, dentry);
int security_inode_killpriv(struct user_namespace *mnt_userns,
	return call_int_hook(inode_killpriv, 0, mnt_userns, dentry);
int security_inode_getsecurity(struct user_namespace *mnt_userns,
	struct security_hook_list *hp;
	int rc;

	/*
	 * Only one module will provide an attribute with a given name.
	 */
	hlist_for_each_entry(hp, &security_hook_heads.inode_getsecurity, list) {
		rc = hp->hook.inode_getsecurity(mnt_userns, inode, name, buffer, alloc);
		if (rc != LSM_RET_DEFAULT(inode_getsecurity))
			return rc;
	}
	return LSM_RET_DEFAULT(inode_getsecurity);
int security_inode_setsecurity(struct inode *inode, const char *name, const void *value, size_t size, int flags)
	struct security_hook_list *hp;
	int rc;

	/*
	 * Only one module will provide an attribute with a given name.
	 */
	hlist_for_each_entry(hp, &security_hook_heads.inode_setsecurity, list) {
		rc = hp->hook.inode_setsecurity(inode, name, value, size,
								flags);
		if (rc != LSM_RET_DEFAULT(inode_setsecurity))
			return rc;
	}
	return LSM_RET_DEFAULT(inode_setsecurity);
int security_inode_listsecurity(struct inode *inode, char *buffer, size_t buffer_size)
	return call_int_hook(inode_listsecurity, 0, inode, buffer, buffer_size);
	return call_int_hook(inode_copy_up, 0, src, new);
int security_inode_copy_up_xattr(const char *name)
	struct security_hook_list *hp;
	/*
	 * The implementation can return 0 (accept the xattr), 1 (discard the
	 * xattr), -EOPNOTSUPP if it does not know anything about the xattr or
	 * any other error code incase of an error.
	 */
	hlist_for_each_entry(hp,
		&security_hook_heads.inode_copy_up_xattr, list) {
		rc = hp->hook.inode_copy_up_xattr(name);
		if (rc != LSM_RET_DEFAULT(inode_copy_up_xattr))
			return rc;
	}
	return call_int_hook(kernfs_init_security, 0, kn_dir, kn);
	int ret;

	ret = call_int_hook(file_permission, 0, file, mask);
	if (ret)
		return ret;

	return fsnotify_perm(file, mask);
EXPORT_SYMBOL_GPL(security_file_permission);
	rc = call_int_hook(file_alloc_security, 0, file);
	return call_int_hook(file_ioctl, 0, file, cmd, arg);
			unsigned long flags)
	int ret;
	ret = call_int_hook(mmap_file, 0, file, prot,
					mmap_prot(file, prot), flags);
	if (ret)
		return ret;
	return ima_file_mmap(file, prot);
	return call_int_hook(mmap_addr, 0, addr);
			    unsigned long prot)
	int ret;

	ret = call_int_hook(file_mprotect, 0, vma, reqprot, prot);
	if (ret)
		return ret;
	return ima_file_mprotect(vma, prot);
	return call_int_hook(file_lock, 0, file, cmd);
	return call_int_hook(file_fcntl, 0, file, cmd, arg);
				  struct fown_struct *fown, int sig)
	return call_int_hook(file_send_sigiotask, 0, tsk, fown, sig);
	return call_int_hook(file_receive, 0, file);
	ret = call_int_hook(file_open, 0, file);
	return fsnotify_perm(file, MAY_OPEN);
	rc = call_int_hook(task_alloc, 0, task, clone_flags);
	rc = call_int_hook(cred_alloc_blank, 0, cred, gfp);
	rc = call_int_hook(cred_prepare, 0, new, old, gfp);
	return call_int_hook(kernel_act_as, 0, new, secid);
	return call_int_hook(kernel_create_files_as, 0, new, inode);
	int ret;

	ret = call_int_hook(kernel_module_request, 0, kmod_name);
	if (ret)
		return ret;
	return integrity_kernel_module_request(kmod_name);
	int ret;

	ret = call_int_hook(kernel_read_file, 0, file, id, contents);
	if (ret)
		return ret;
	return ima_read_file(file, id, contents);
	int ret;

	ret = call_int_hook(kernel_post_read_file, 0, file, buf, size, id);
	if (ret)
		return ret;
	return ima_post_read_file(file, buf, size, id);
	int ret;

	ret = call_int_hook(kernel_load_data, 0, id, contents);
	if (ret)
		return ret;
	return ima_load_data(id, contents);
	int ret;

	ret = call_int_hook(kernel_post_load_data, 0, buf, size, id,
			    description);
	if (ret)
		return ret;
	return ima_post_load_data(buf, size, id, description);
	return call_int_hook(task_fix_setuid, 0, new, old, flags);
				 int flags)
	return call_int_hook(task_fix_setgid, 0, new, old, flags);
	return call_int_hook(task_setpgid, 0, p, pgid);
	return call_int_hook(task_getpgid, 0, p);
	return call_int_hook(task_getsid, 0, p);
void security_task_getsecid_subj(struct task_struct *p, u32 *secid)
	call_void_hook(task_getsecid_subj, p, secid);
EXPORT_SYMBOL(security_task_getsecid_subj);
	return call_int_hook(task_setnice, 0, p, nice);
	return call_int_hook(task_setioprio, 0, p, ioprio);
	return call_int_hook(task_getioprio, 0, p);
	return call_int_hook(task_prlimit, 0, cred, tcred, flags);
		struct rlimit *new_rlim)
	return call_int_hook(task_setrlimit, 0, p, resource, new_rlim);
	return call_int_hook(task_setscheduler, 0, p);
	return call_int_hook(task_getscheduler, 0, p);
	return call_int_hook(task_movememory, 0, p);
			int sig, const struct cred *cred)
	return call_int_hook(task_kill, 0, p, info, sig, cred);
			 unsigned long arg4, unsigned long arg5)
	struct security_hook_list *hp;
	hlist_for_each_entry(hp, &security_hook_heads.task_prctl, list) {
		thisrc = hp->hook.task_prctl(option, arg2, arg3, arg4, arg5);
	return call_int_hook(ipc_permission, 0, ipcp, flag);
	rc = call_int_hook(msg_msg_alloc_security, 0, msg);
	rc = call_int_hook(msg_queue_alloc_security, 0, msq);
	return call_int_hook(msg_queue_associate, 0, msq, msqflg);
	return call_int_hook(msg_queue_msgctl, 0, msq, cmd);
			       struct msg_msg *msg, int msqflg)
	return call_int_hook(msg_queue_msgsnd, 0, msq, msg, msqflg);
			       struct task_struct *target, long type, int mode)
	return call_int_hook(msg_queue_msgrcv, 0, msq, msg, target, type, mode);
	rc = call_int_hook(shm_alloc_security, 0, shp);
	return call_int_hook(shm_associate, 0, shp, shmflg);
	return call_int_hook(shm_shmctl, 0, shp, cmd);
int security_shm_shmat(struct kern_ipc_perm *shp, char __user *shmaddr, int shmflg)
	return call_int_hook(shm_shmat, 0, shp, shmaddr, shmflg);
	rc = call_int_hook(sem_alloc_security, 0, sma);
	return call_int_hook(sem_associate, 0, sma, semflg);
	return call_int_hook(sem_semctl, 0, sma, cmd);
			unsigned nsops, int alter)
	return call_int_hook(sem_semop, 0, sma, sops, nsops, alter);
int security_getprocattr(struct task_struct *p, const char *lsm, char *name,
				char **value)
	struct security_hook_list *hp;
	hlist_for_each_entry(hp, &security_hook_heads.getprocattr, list) {
		if (lsm != NULL && strcmp(lsm, hp->lsm))
		return hp->hook.getprocattr(p, name, value);
int security_setprocattr(const char *lsm, const char *name, void *value,
			 size_t size)
	struct security_hook_list *hp;
	hlist_for_each_entry(hp, &security_hook_heads.setprocattr, list) {
		if (lsm != NULL && strcmp(lsm, hp->lsm))
		return hp->hook.setprocattr(name, value, size);
	return call_int_hook(netlink_send, 0, sk, skb);
	return call_int_hook(ismaclabel, 0, name);
	struct security_hook_list *hp;
	int rc;

	/*
	 * Currently, only one LSM can implement secid_to_secctx (i.e this
	 * LSM hook is not "stackable").
	 */
	hlist_for_each_entry(hp, &security_hook_heads.secid_to_secctx, list) {
		rc = hp->hook.secid_to_secctx(secid, secdata, seclen);
		if (rc != LSM_RET_DEFAULT(secid_to_secctx))
			return rc;
	}

	return LSM_RET_DEFAULT(secid_to_secctx);
	return call_int_hook(secctx_to_secid, 0, secdata, seclen, secid);
	return call_int_hook(inode_notifysecctx, 0, inode, ctx, ctxlen);
	return call_int_hook(inode_setsecctx, 0, dentry, ctx, ctxlen);
	return call_int_hook(inode_getsecctx, -EOPNOTSUPP, inode, ctx, ctxlen);
	return call_int_hook(post_notification, 0, w_cred, cred, n);
	return call_int_hook(watch_key, 0, key);
#endif

int security_unix_stream_connect(struct sock *sock, struct sock *other, struct sock *newsk)
	return call_int_hook(unix_stream_connect, 0, sock, other, newsk);
	return call_int_hook(unix_may_send, 0, sock, other);
	return call_int_hook(socket_create, 0, family, type, protocol, kern);
	return call_int_hook(socket_post_create, 0, sock, family, type,
						protocol, kern);
	return call_int_hook(socket_socketpair, 0, socka, sockb);
int security_socket_bind(struct socket *sock, struct sockaddr *address, int addrlen)
	return call_int_hook(socket_bind, 0, sock, address, addrlen);
int security_socket_connect(struct socket *sock, struct sockaddr *address, int addrlen)
	return call_int_hook(socket_connect, 0, sock, address, addrlen);
	return call_int_hook(socket_listen, 0, sock, backlog);
	return call_int_hook(socket_accept, 0, sock, newsock);
	return call_int_hook(socket_sendmsg, 0, sock, msg, size);
	return call_int_hook(socket_recvmsg, 0, sock, msg, size, flags);
	return call_int_hook(socket_getsockname, 0, sock);
	return call_int_hook(socket_getpeername, 0, sock);
	return call_int_hook(socket_getsockopt, 0, sock, level, optname);
	return call_int_hook(socket_setsockopt, 0, sock, level, optname);
	return call_int_hook(socket_shutdown, 0, sock, how);
	return call_int_hook(socket_sock_rcv_skb, 0, sk, skb);
int security_socket_getpeersec_stream(struct socket *sock, char __user *optval,
				      int __user *optlen, unsigned len)
	return call_int_hook(socket_getpeersec_stream, -ENOPROTOOPT, sock,
				optval, optlen, len);
int security_socket_getpeersec_dgram(struct socket *sock, struct sk_buff *skb, u32 *secid)
	return call_int_hook(socket_getpeersec_dgram, -ENOPROTOOPT, sock,
			     skb, secid);
	return call_int_hook(sk_alloc_security, 0, sk, family, priority);
void security_sk_classify_flow(struct sock *sk, struct flowi_common *flic)
			struct sk_buff *skb, struct request_sock *req)
	return call_int_hook(inet_conn_request, 0, sk, skb, req);
			const struct request_sock *req)
			struct sk_buff *skb)
	return call_int_hook(secmark_relabel_packet, 0, secid);
	return call_int_hook(tun_dev_alloc_security, 0, security);
	call_void_hook(tun_dev_free_security, security);
	return call_int_hook(tun_dev_create, 0);
	return call_int_hook(tun_dev_attach_queue, 0, security);
	return call_int_hook(tun_dev_attach, 0, sk, security);
	return call_int_hook(tun_dev_open, 0, security);
int security_sctp_assoc_request(struct sctp_association *asoc, struct sk_buff *skb)
	return call_int_hook(sctp_assoc_request, 0, asoc, skb);
	return call_int_hook(sctp_bind_connect, 0, sk, optname,
			     address, addrlen);

	return call_int_hook(ib_pkey_access, 0, sec, subnet_prefix, pkey);
int security_ib_endport_manage_subnet(void *sec, const char *dev_name, u8 port_num)
	return call_int_hook(ib_endport_manage_subnet, 0, sec, dev_name, port_num);
	return call_int_hook(ib_alloc_security, 0, sec);
	call_void_hook(ib_free_security, sec);

	return call_int_hook(xfrm_policy_alloc_security, 0, ctxp, sec_ctx, gfp);
			      struct xfrm_sec_ctx **new_ctxp)
	return call_int_hook(xfrm_policy_clone_security, 0, old_ctx, new_ctxp);
	return call_int_hook(xfrm_policy_delete_security, 0, ctx);
	return call_int_hook(xfrm_state_alloc, 0, x, sec_ctx);
	return call_int_hook(xfrm_state_alloc_acquire, 0, x, polsec, secid);
	return call_int_hook(xfrm_state_delete_security, 0, x);
	return call_int_hook(xfrm_policy_lookup, 0, ctx, fl_secid);
	struct security_hook_list *hp;
	hlist_for_each_entry(hp, &security_hook_heads.xfrm_state_pol_flow_match,
				list) {
		rc = hp->hook.xfrm_state_pol_flow_match(x, xp, flic);
	return call_int_hook(xfrm_decode_session, 0, skb, secid, 1);
	int rc = call_int_hook(xfrm_decode_session, 0, skb, &flic->flowic_secid,
				0);


	return call_int_hook(key_alloc, 0, key, cred, flags);
	call_void_hook(key_free, key);
	return call_int_hook(key_permission, 0, key_ref, cred, need_perm);
int security_key_getsecurity(struct key *key, char **_buffer)
	*_buffer = NULL;
	return call_int_hook(key_getsecurity, 0, key, _buffer);

int security_audit_rule_init(u32 field, u32 op, char *rulestr, void **lsmrule)
	return call_int_hook(audit_rule_init, 0, field, op, rulestr, lsmrule);
	return call_int_hook(audit_rule_known, 0, krule);
	return call_int_hook(audit_rule_match, 0, secid, field, op, lsmrule);
	return call_int_hook(bpf, 0, cmd, attr, size);
	return call_int_hook(bpf_map, 0, map, fmode);
	return call_int_hook(bpf_prog, 0, prog);
int security_bpf_map_alloc(struct bpf_map *map)
	return call_int_hook(bpf_map_alloc_security, 0, map);
int security_bpf_prog_alloc(struct bpf_prog_aux *aux)
	return call_int_hook(bpf_prog_alloc_security, 0, aux);
	call_void_hook(bpf_map_free_security, map);
void security_bpf_prog_free(struct bpf_prog_aux *aux)
	call_void_hook(bpf_prog_free_security, aux);
	return call_int_hook(locked_down, 0, what);
	return call_int_hook(perf_event_open, 0, attr, type);
	return call_int_hook(perf_event_alloc, 0, event);
	call_void_hook(perf_event_free, event);
	return call_int_hook(perf_event_read, 0, event);
	return call_int_hook(perf_event_write, 0, event);
	return call_int_hook(uring_override_creds, 0, new);
	return call_int_hook(uring_sqpoll, 0);