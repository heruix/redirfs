/*
 * RedirFS: Redirecting File System
 * Written by Frantisek Hrbata <frantisek.hrbata@redirfs.org>
 *
 * Copyright (C) 2008 Frantisek Hrbata
 * All rights reserved.
 *
 * This file is part of RedirFS.
 *
 * RedirFS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RedirFS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RedirFS. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _REDIRFS_H
#define _REDIRFS_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/types.h>
#include <linux/aio.h>

#define REDIRFS_VERSION "0.3"

#define REDIRFS_PATH_ADD		1
#define REDIRFS_PATH_REM		2
#define REDIRFS_PATH_INCLUDE		4
#define REDIRFS_PATH_EXCLUDE		8

#define REDIRFS_CTL_ACTIVATE		1
#define REDIRFS_CTL_DEACTIVATE		2
#define REDIRFS_CTL_SET_PATH		4
#define REDIRFS_CTL_UNREGISTER		8
#define REDIRFS_CTL_REMOVE_PATHS	16

#define REDIRFS_FILTER_ATTRIBUTE(__name, __mode, __show, __store) \
	__ATTR(__name, __mode, __show, __store)

enum redirfs_op_id {
	REDIRFS_NONE_DOP_D_REVALIDATE,
	REDIRFS_NONE_DOP_D_HASH,
	REDIRFS_NONE_DOP_D_COMPARE,
	REDIRFS_NONE_DOP_D_DELETE,
	REDIRFS_NONE_DOP_D_RELEASE,
	REDIRFS_NONE_DOP_D_IPUT,
	REDIRFS_NODE_DOP_D_NAME,

	REDIRFS_REG_DOP_D_REVALIDATE,
	REDIRFS_REG_DOP_D_HASH,
	REDIRFS_REG_DOP_D_COMPARE,
	REDIRFS_REG_DOP_D_DELETE,
	REDIRFS_REG_DOP_D_IPUT,
	REDIRFS_REG_DOP_D_NAME,

	REDIRFS_DIR_DOP_D_REVALIDATE,
	REDIRFS_DIR_DOP_D_HASH,
	REDIRFS_DIR_DOP_D_COMPARE,
	REDIRFS_DIR_DOP_D_DELETE,
	REDIRFS_DIR_DOP_D_IPUT,
	REDIRFS_DIR_DOP_D_NAME,

	REDIRFS_CHR_DOP_D_REVALIDATE,
	REDIRFS_CHR_DOP_D_HASH,
	REDIRFS_CHR_DOP_D_COMPARE,
	REDIRFS_CHR_DOP_D_DELETE,
	REDIRFS_CHR_DOP_D_IPUT,
	REDIRFS_CHR_DOP_D_NAME,

	REDIRFS_BLK_DOP_D_REVALIDATE,
	REDIRFS_BLK_DOP_D_HASH,
	REDIRFS_BLK_DOP_D_COMPARE,
	REDIRFS_BLK_DOP_D_DELETE,
	REDIRFS_BLK_DOP_D_IPUT,
	REDIRFS_BLK_DOP_D_NAME,

	REDIRFS_FIFO_DOP_D_REVALIDATE,
	REDIRFS_FIFO_DOP_D_HASH,
	REDIRFS_FIFO_DOP_D_COMPARE,
	REDIRFS_FIFO_DOP_D_DELETE,
	REDIRFS_FIFO_DOP_D_IPUT,
	REDIRFS_FIFO_DOP_D_NAME,

	REDIRFS_LNK_DOP_D_REVALIDATE,
	REDIRFS_LNK_DOP_D_HASH,
	REDIRFS_LNK_DOP_D_COMPARE,
	REDIRFS_LNK_DOP_D_DELETE,
	REDIRFS_LNK_DOP_D_IPUT,
	REDIRFS_LNK_DOP_D_NAME,

	REDIRFS_SOCK_DOP_D_REVALIDATE,
	REDIRFS_SOCK_DOP_D_HASH,
	REDIRFS_SOCK_DOP_D_COMPARE,
	REDIRFS_SOCK_DOP_D_DELETE,
	REDIRFS_SOCK_DOP_D_IPUT,
	REDIRFS_SOCK_DOP_D_NAME,

	REDIRFS_REG_IOP_PERMISSION,
	REDIRFS_REG_IOP_SETATTR,

	REDIRFS_DIR_IOP_CREATE,
	REDIRFS_DIR_IOP_LOOKUP,
	REDIRFS_DIR_IOP_LINK,
	REDIRFS_DIR_IOP_UNLINK,
	REDIRFS_DIR_IOP_SYMLINK,
	REDIRFS_DIR_IOP_MKDIR,
	REDIRFS_DIR_IOP_RMDIR,
	REDIRFS_DIR_IOP_MKNOD,
	REDIRFS_DIR_IOP_RENAME,
	REDIRFS_DIR_IOP_PERMISSION,
	REDIRFS_DIR_IOP_SETATTR,

	REDIRFS_CHR_IOP_PERMISSION,
	REDIRFS_CHR_IOP_SETATTR,

	REDIRFS_BLK_IOP_PERMISSION,
	REDIRFS_BLK_IOP_SETATTR,

	REDIRFS_FIFO_IOP_PERMISSION,
	REDIRFS_FIFO_IOP_SETATTR,

	REDIRFS_LNK_IOP_PERMISSION,
	REDIRFS_LNK_IOP_SETATTR,

	REDIRFS_SOCK_IOP_PERMISSION,
	REDIRFS_SOCK_IOP_SETATTR,

	REDIRFS_REG_FOP_OPEN,
	REDIRFS_REG_FOP_RELEASE,
	REDIRFS_REG_FOP_LLSEEK,
	REDIRFS_REG_FOP_READ,
	REDIRFS_REG_FOP_WRITE,
	REDIRFS_REG_FOP_AIO_READ,
	REDIRFS_REG_FOP_AIO_WRITE,
	REDIRFS_REG_FOP_MMAP,
	REDIRFS_REG_FOP_FLUSH,

	REDIRFS_DIR_FOP_OPEN,
	REDIRFS_DIR_FOP_RELEASE,
	REDIRFS_DIR_FOP_READDIR,
	REDIRFS_DIR_FOP_FLUSH,

	REDIRFS_CHR_FOP_OPEN,
	REDIRFS_CHR_FOP_RELEASE,
	REDIRFS_CHR_FOP_LLSEEK,
	REDIRFS_CHR_FOP_READ,
	REDIRFS_CHR_FOP_WRITE,
	REDIRFS_CHR_FOP_AIO_READ,
	REDIRFS_CHR_FOP_AIO_WRITE,
	REDIRFS_CHR_FOP_FLUSH,

	REDIRFS_BLK_FOP_OPEN,
	REDIRFS_BLK_FOP_RELEASE,
	REDIRFS_BLK_FOP_LLSEEK,
	REDIRFS_BLK_FOP_READ,
	REDIRFS_BLK_FOP_WRITE,
	REDIRFS_BLK_FOP_AIO_READ,
	REDIRFS_BLK_FOP_AIO_WRITE,
	REDIRFS_BLK_FOP_FLUSH,

	REDIRFS_FIFO_FOP_OPEN,
	REDIRFS_FIFO_FOP_RELEASE,
	REDIRFS_FIFO_FOP_LLSEEK,
	REDIRFS_FIFO_FOP_READ,
	REDIRFS_FIFO_FOP_WRITE,
	REDIRFS_FIFO_FOP_AIO_READ,
	REDIRFS_FIFO_FOP_AIO_WRITE,
	REDIRFS_FIFO_FOP_FLUSH,

	REDIRFS_LNK_FOP_OPEN,
	REDIRFS_LNK_FOP_RELEASE,
	REDIRFS_LNK_FOP_LLSEEK,
	REDIRFS_LNK_FOP_READ,
	REDIRFS_LNK_FOP_WRITE,
	REDIRFS_LNK_FOP_AIO_READ,
	REDIRFS_LNK_FOP_AIO_WRITE,
	REDIRFS_LNK_FOP_FLUSH,

	REDIRFS_REG_AOP_READPAGE,
	REDIRFS_REG_AOP_WRITEPAGE,
	REDIRFS_REG_AOP_READPAGES,
	REDIRFS_REG_AOP_WRITEPAGES,
	REDIRFS_REG_AOP_SYNC_PAGE,
	REDIRFS_REG_AOP_SET_PAGE_DIRTY,
	REDIRFS_REG_AOP_PREPARE_WRITE,
	REDIRFS_REG_AOP_COMMIT_WRITE,
	REDIRFS_REG_AOP_BMAP,
	REDIRFS_REG_AOP_INVALIDATEPAGE,
	REDIRFS_REG_AOP_RELEASEPAGE,
	REDIRFS_REG_AOP_DIRECT_IO,
	REDIRFS_REG_AOP_GET_XIP_PAGE,
	REDIRFS_REG_AOP_MIGRATEPAGE,
	REDIRFS_REG_AOP_LAUNDER_PAGE,

	REDIRFS_OP_END
};

enum redirfs_op_call {
	REDIRFS_PRECALL,
	REDIRFS_POSTCALL
};

enum redirfs_rv {
	REDIRFS_STOP,
	REDIRFS_CONTINUE
};

typedef void *redirfs_filter;
typedef void *redirfs_context;
typedef void *redirfs_path;

union redirfs_op_rv {
	int		rv_int;
	ssize_t		rv_ssize;
	unsigned int	rv_uint;
	unsigned long	rv_ulong;
	loff_t		rv_loff;
	struct dentry	*rv_dentry;
	sector_t	rv_sector;
	struct page	*rv_page;
};

union redirfs_op_args {
	struct {
		struct dentry *dentry;
		struct nameidata *nd;
	} d_revalidate;	

	struct {
		struct dentry *dentry;
		struct qstr *name;
	} d_hash;

	struct {
		struct dentry *dentry;
		struct qstr *name1;
		struct qstr *name2;
	} d_compare;

	struct {
		struct dentry *dentry;
	} d_delete;

	struct {
		struct dentry *dentry;
	} d_release;

	struct {
		struct dentry *dentry;
		struct inode *inode;
	} d_iput;	

	struct {
		struct inode *dir;
		struct dentry *dentry;
		int mode;
		struct nameidata *nd;
	} i_create;

	struct {
		struct inode *dir;
		struct dentry *dentry;
		struct nameidata *nd;
	} i_lookup;

	struct {
		struct dentry *old_dentry;
		struct inode *dir;
		struct dentry *dentry;
	} i_link;

	struct {
		struct inode *dir;
		struct dentry *dentry;
	} i_unlink;

	struct {
		struct inode *dir;
		struct dentry *dentry;
		const char *oldname;
	} i_symlink;

	struct {
		struct inode *dir;
		struct dentry *dentry;
		int mode;
	} i_mkdir;

	struct {
		struct inode *dir;
		struct dentry *dentry;
	} i_rmdir;

	struct {
		struct inode *dir;
		struct dentry *dentry;
		int mode;
		dev_t rdev;
	} i_mknod;

	struct {
		struct inode *old_dir;
		struct dentry *old_dentry;
		struct inode *new_dir;
		struct dentry *new_dentry;
	} i_rename;

	struct {
		struct inode *inode;
		int mask;
		struct nameidata *nd;
	} i_permission;

	struct {
		struct dentry *dentry;
		struct iattr *iattr;
	} i_setattr;

	struct {
		struct inode *inode;
		struct file *file;
	} f_open;

	struct {
		struct inode *inode;
		struct file *file;
	} f_release;

	struct {
		struct file *file;
		fl_owner_t id;
	} f_flush;

	struct {
		struct file *file;
		struct vm_area_struct *vma;
	} f_mmap;

	struct {
		struct file *file;
		void *buf;
		filldir_t filldir;
	} f_readdir;

	struct {
                struct file *file;
                loff_t offset;
                int origin;
	} f_llseek;

	struct {
		struct file *file;
		char __user *buf;
		size_t count;
		loff_t *pos;
	} f_read;

	struct {
		struct file *file;
		const char __user *buf;
		size_t count;
		loff_t *pos;
	} f_write;

	struct {
		struct kiocb *iocb;
		const struct iovec *iov;
		unsigned long nr_segs;
		loff_t pos;
	} f_aio_read;

	struct {
		struct kiocb *iocb;
		const struct iovec *iov;
		unsigned long nr_segs;
		loff_t pos;
	} f_aio_write;

	struct {
		struct file *file;
		struct page *page;
	} a_readpage;

	struct {
		struct page *page;
		struct writeback_control *wbc;
	} a_writepage;

	struct {
		struct file *file;
		struct address_space *mapping;
		struct list_head *pages;
		unsigned nr_pages;
	} a_readpages;

	struct {
		struct address_space *mapping;
		struct writeback_control *wbc;
	} a_writepages;

	struct {
		struct page *page;
	} a_sync_page;

	struct {
		struct page *page;
	} a_set_page_dirty;

	struct {
		struct file *file;
		struct page *page;
		unsigned from;
		unsigned to;
	} a_prepare_write;

	struct {
		struct file *file;
		struct page *page;
		unsigned from;
		unsigned to;
	} a_commit_write;

	struct {
		struct address_space *mapping;
		sector_t block;
	} a_bmap;

	struct {
		struct page *page;
		unsigned long offset;
	} a_invalidatepage;

	struct {
		struct page *page;
		gfp_t flags;
	} a_releasepage;

	struct {
		int rw;
		struct kiocb *iocb;
		const struct iovec *iov;
		loff_t offset;
		unsigned long nr_segs;
	} a_direct_IO;

	struct {
		struct address_space *mapping;
		sector_t offset;
		int create;
	} a_get_xip_page;

	struct {
		struct address_space *mapping;
		struct page *newpage;
		struct page *page;
	} a_migratepage;

	struct {
		struct page *page;
	} a_launder_page;
};

struct redirfs_op_type {
	enum redirfs_op_id id;
	enum redirfs_op_call call;
};

struct redirfs_args {
	union redirfs_op_args args;
	union redirfs_op_rv rv;
	struct redirfs_op_type type;
};

struct redirfs_path_info {
	struct dentry *dentry;
	struct vfsmount *mnt;
	int flags;
};

struct redirfs_op_info {
	enum redirfs_op_id op_id;
	enum redirfs_rv (*pre_cb)(redirfs_context, struct redirfs_args *);
	enum redirfs_rv (*post_cb)(redirfs_context, struct redirfs_args *);
};

struct redirfs_paths {
	redirfs_path *path;
	int nr;
};

union redirfs_ctl_data {
	struct redirfs_path_info path_info;
};

struct redirfs_ctl {
	int id;
	union redirfs_ctl_data data;
};

struct redirfs_filter_info {
	struct module *owner;
	const char *name;
	int priority;
	int active;
	int ctl_id;
	int (*ctl_cb)(struct redirfs_ctl *ctl);
};

struct redirfs_filter_attribute {
	struct attribute attr;
	ssize_t (*show)(redirfs_filter filter,
			struct redirfs_filter_attribute *attr, char *buf);
	ssize_t (*store)(redirfs_filter filter,
			struct redirfs_filter_attribute *attr, const char *buf,
			size_t count);
};

int redirfs_create_attribute(redirfs_filter filter,
		struct redirfs_filter_attribute *attr);
int redirfs_remove_attribute(redirfs_filter filter,
		struct redirfs_filter_attribute *attr);
struct kobject *redirfs_filter_kobject(redirfs_filter filter);
int redirfs_set_path(redirfs_filter filter, struct redirfs_path_info *info);
int redirfs_get_path(redirfs_filter filter, struct redirfs_path_info *info,
		redirfs_path *path);
void redirfs_put_path(redirfs_path *path);
int redirfs_get_paths(redirfs_filter filter, struct redirfs_paths *paths);
void redirfs_put_paths(struct redirfs_paths *paths);
int redirfs_get_path_info(redirfs_filter filter, redirfs_path path,
		struct redirfs_path_info *info);
int redirfs_remove_paths(redirfs_filter filter);
int redirfs_register_filter(redirfs_filter *filter,
		struct redirfs_filter_info *info);
int redirfs_unregister_filter(redirfs_filter filter);
void redirfs_delete_filter(redirfs_filter filter);
int redirfs_set_operations(redirfs_filter filter, struct redirfs_op_info ops[]);
int redirfs_activate_filter(redirfs_filter filter);
int redirfs_deactivate_filter(redirfs_filter filter);
int redirfs_get_filename(struct vfsmount *mnt, struct dentry *dentry, char *buf,
		int size);

#endif

