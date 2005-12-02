#include <linux/module.h>
#include "operations.h"
#include "filter.h"
#include "root.h"
#include "debug.h"

void ***redirfs_gettype(int type, struct redirfs_operations_t *ops)
{
	void ***rv = NULL;


	redirfs_debug("started");

	switch (type) {
		case REDIRFS_I_REG:
			rv = ops->reg_iops_arr;
			break;
		case REDIRFS_I_DIR:
			rv = ops->dir_iops_arr;
			break;
		case REDIRFS_F_REG:
			rv = ops->reg_fops_arr;
			break;
		case REDIRFS_F_DIR:
			rv = ops->dir_fops_arr;
			break;
		case REDIRFS_DENTRY:
			rv = ops->dops_arr;
			break;
		default:
			BUG();
	}

	redirfs_debug("ended");

	return rv;
}

unsigned int *redirfs_getcnt(int type, struct redirfs_operations_counters_t *cnts) 
{
	unsigned int  *rv = NULL;


	redirfs_debug("started");

	switch (type) {
		case REDIRFS_I_REG:
			rv = cnts->reg_iops_cnt;
			break;
		case REDIRFS_I_DIR:
			rv = cnts->dir_iops_cnt;
			break;
		case REDIRFS_F_REG:
			rv = cnts->reg_fops_cnt;
			break;
		case REDIRFS_F_DIR:
			rv = cnts->dir_fops_cnt;
			break;
		case REDIRFS_DENTRY:
			rv = cnts->dops_cnt;
			break;
		default:
			BUG();
	}

	redirfs_debug("ended");

	return rv;
}


void redirfs_init_iops_arr(void ***arr, struct inode_operations *iops)
{
	redirfs_debug("started");

	arr[REDIRFS_IOP_CREATE]	= (void**)&iops->create; 
	arr[REDIRFS_IOP_LOOKUP] = (void**)&iops->lookup; 
	arr[REDIRFS_IOP_LINK] = (void**)&iops->link; 
	arr[REDIRFS_IOP_UNLINK] = (void**)&iops->unlink; 
	arr[REDIRFS_IOP_SYMLINK] = (void**)&iops->symlink; 
	arr[REDIRFS_IOP_MKDIR] = (void**)&iops->mkdir; 
	arr[REDIRFS_IOP_RMDIR] = (void**)&iops->rmdir; 
	arr[REDIRFS_IOP_MKNOD] = (void**)&iops->mknod; 
	arr[REDIRFS_IOP_RENAME] = (void**)&iops->rename; 
	arr[REDIRFS_IOP_READLINK] = (void**)&iops->readlink; 
	arr[REDIRFS_IOP_FOLLOW_LINK] = (void**)&iops->follow_link; 
	arr[REDIRFS_IOP_PUT_LINK] = (void**)&iops->put_link; 
	arr[REDIRFS_IOP_TRUNCATE] = (void**)&iops->truncate; 
	arr[REDIRFS_IOP_PERMISSION] = (void**)&iops->permission; 
	arr[REDIRFS_IOP_SETATTR] = (void**)&iops->setattr; 
	arr[REDIRFS_IOP_GETATTR] = (void**)&iops->getattr; 
	arr[REDIRFS_IOP_SETXATTR] = (void**)&iops->setxattr; 
	arr[REDIRFS_IOP_GETXATTR] = (void**)&iops->getxattr; 
	arr[REDIRFS_IOP_LISTXATTR] = (void**)&iops->listxattr; 
	arr[REDIRFS_IOP_REMOVEXATTR] = (void**)&iops->removexattr; 

	redirfs_debug("ended");
}

void redirfs_init_fops_arr(void ***arr, struct file_operations *fops)
{
	redirfs_debug("started");

	arr[REDIRFS_FOP_LLSEEK] = (void**)&fops->llseek; 
	arr[REDIRFS_FOP_READ] = (void**)&fops->read; 
	arr[REDIRFS_FOP_AIO_READ] = (void**)&fops->aio_read; 
	arr[REDIRFS_FOP_WRITE] = (void**)&fops->write; 
	arr[REDIRFS_FOP_AIO_WRITE] = (void**)&fops->aio_write; 
	arr[REDIRFS_FOP_READDIR] = (void**)&fops->readdir; 
	arr[REDIRFS_FOP_POLL] = (void**)&fops->poll; 
	arr[REDIRFS_FOP_IOCTL] = (void**)&fops->ioctl; 
	arr[REDIRFS_FOP_MMAP] = (void**)&fops->mmap; 
	arr[REDIRFS_FOP_OPEN] = (void**)&fops->open; 
	arr[REDIRFS_FOP_FLUSH] = (void**)&fops->flush; 
	arr[REDIRFS_FOP_RELEASE] = (void**)&fops->release; 
	arr[REDIRFS_FOP_FSYNC] = (void**)&fops->fsync; 
	arr[REDIRFS_FOP_AIO_FSYNC] = (void**)&fops->aio_fsync; 
	arr[REDIRFS_FOP_FASYNC] = (void**)&fops->fasync; 
	arr[REDIRFS_FOP_LOCK] = (void**)&fops->lock; 
	arr[REDIRFS_FOP_READV] = (void**)&fops->readv; 
	arr[REDIRFS_FOP_WRITEV] = (void**)&fops->writev; 
	arr[REDIRFS_FOP_SENDFILE] = (void**)&fops->sendfile; 
	arr[REDIRFS_FOP_SENDPAGE] = (void**)&fops->sendpage; 
	arr[REDIRFS_FOP_GET_UNMAPPED_AREA] = (void**)&fops->get_unmapped_area; 
	arr[REDIRFS_FOP_CHECK_FLAGS] = (void**)&fops->check_flags; 
	arr[REDIRFS_FOP_DIR_NOTIFY] = (void**)&fops->dir_notify; 
	arr[REDIRFS_FOP_FLOCK] = (void**)&fops->flock;

	redirfs_debug("ended");
}

void redirfs_init_dops_arr(void ***arr, struct dentry_operations *dops) 
{
	redirfs_debug("started");

	arr[REDIRFS_DOP_REVALIDATE] = (void**)&dops->d_revalidate;
	arr[REDIRFS_DOP_HASH] = (void**)&dops->d_hash;
	arr[REDIRFS_DOP_COMPARE] = (void**)&dops->d_compare;
	arr[REDIRFS_DOP_DELETE] = (void**)&dops->d_delete;
	arr[REDIRFS_DOP_RELEASE] = (void**)&dops->d_release;
	arr[REDIRFS_DOP_IPUT] = (void**)&dops->d_iput;

	redirfs_debug("ended");
}

void redirfs_init_ops(struct redirfs_operations_t *ops, struct redirfs_vfs_operations_t *vfs_ops)
{
	redirfs_debug("started");

	memset(vfs_ops, 0, sizeof(struct redirfs_vfs_operations_t));
	ops->reg_iops = &vfs_ops->reg_iops;
	ops->dir_iops = &vfs_ops->dir_iops;
	ops->reg_fops = &vfs_ops->reg_fops;
	ops->dir_fops = &vfs_ops->dir_fops;
	ops->dops = &vfs_ops->dops;
	redirfs_init_iops_arr(ops->reg_iops_arr, ops->reg_iops); 
	redirfs_init_iops_arr(ops->dir_iops_arr, ops->dir_iops); 
	redirfs_init_fops_arr(ops->reg_fops_arr, ops->reg_fops); 
	redirfs_init_fops_arr(ops->dir_fops_arr, ops->dir_fops); 
	redirfs_init_dops_arr(ops->dops_arr, ops->dops); 
	ops->ops_arr_sizes[REDIRFS_I_REG] = REDIRFS_IOP_END;
	ops->ops_arr_sizes[REDIRFS_I_DIR] = REDIRFS_IOP_END;
	ops->ops_arr_sizes[REDIRFS_F_REG] = REDIRFS_FOP_END;
	ops->ops_arr_sizes[REDIRFS_F_DIR] = REDIRFS_FOP_END;
	ops->ops_arr_sizes[REDIRFS_DENTRY] = REDIRFS_DOP_END;

	redirfs_debug("ended");
}

void redirfs_init_cnts(struct redirfs_operations_counters_t *cnts)
{
	redirfs_debug("started");

	memset(cnts, 0, sizeof(struct redirfs_operations_counters_t));

	redirfs_debug("ended");
}

void redirfs_init_orig_ops(struct redirfs_operations_t *ops)
{
	redirfs_debug("started");

	ops->reg_iops = NULL;
	ops->dir_iops = NULL;
	ops->reg_fops = NULL;
	ops->dir_fops = NULL;
	ops->dops = NULL;
	ops->reg_iops_arr[0] = NULL;
	ops->dir_iops_arr[0] = NULL;
	ops->reg_fops_arr[0] = NULL;
	ops->dir_fops_arr[0] = NULL;
	ops->dops_arr[0] = NULL;
	ops->ops_arr_sizes[REDIRFS_I_REG] = REDIRFS_IOP_END;
	ops->ops_arr_sizes[REDIRFS_I_DIR] = REDIRFS_IOP_END;
	ops->ops_arr_sizes[REDIRFS_F_REG] = REDIRFS_FOP_END;
	ops->ops_arr_sizes[REDIRFS_F_DIR] = REDIRFS_FOP_END;
	ops->ops_arr_sizes[REDIRFS_DENTRY] = REDIRFS_DOP_END;

	redirfs_debug("ended");
}

struct redirfs_cb_data_t {
	struct redirfs_flt_t *flt;
	int i_val;
	int type;
	int op;
};

static int redirfs_set_flt_ops(struct redirfs_root_t *root, void *data)
{
	struct redirfs_cb_data_t *cb_data = (struct redirfs_cb_data_t *)data;
	struct redirfs_flt_t *flt = cb_data->flt;
	int inc_op = cb_data->i_val;
	int type = cb_data->type;
	int op = cb_data->op;
	void ***new_ops;
	void ***orig_ops;
	void ***fw_ops;
	unsigned int *cnts;


	redirfs_debug("started");

	if (redirfs_flt_arr_get(&root->attached_flts, flt) >= 0) {
		spin_lock(&root->lock);

		orig_ops = redirfs_gettype(type, &root->orig_ops);

		if (orig_ops[0]) {
			new_ops = redirfs_gettype(type, &root->new_ops);
			fw_ops = redirfs_gettype(type, root->fw_ops);

			if (*new_ops[op] != *fw_ops[op]) {
				cnts = redirfs_getcnt(type, &root->new_ops_cnts);

				*new_ops[op] = fw_ops[op];
				cnts[op] += inc_op;
			}
		}

		spin_unlock(&root->lock);
	}

	redirfs_debug("ended");
	return 0;
}

static int redirfs_remove_flt_ops(struct redirfs_root_t *root, void *data)
{
	struct redirfs_cb_data_t *cb_data = (struct redirfs_cb_data_t *)data;
	struct redirfs_flt_t *flt = cb_data->flt;
	int dec_op = cb_data->i_val;
	int type = cb_data->type;
	int op = cb_data->op;
	void ***orig_ops;
	void ***new_ops;
	unsigned int *cnts;


	redirfs_debug("started");

	if (redirfs_flt_arr_get(&root->attached_flts, flt) >= 0) {
		spin_lock(&root->lock);

		orig_ops = redirfs_gettype(type, &root->orig_ops);

		if (orig_ops[0]) {
			cnts = redirfs_getcnt(type, &root->new_ops_cnts);
			cnts[op] -= dec_op;

			if (!cnts[op]) {
				new_ops = redirfs_gettype(type, &root->new_ops);
				*new_ops[op] = *orig_ops[op];
			}
		}

		spin_unlock(&root->lock);
	}

	redirfs_debug("ended");

	return 0;
}

int redirfs_set_operations(redirfs_filter filter, struct redirfs_op_t ops[])
{
	struct redirfs_flt_t *flt;
	struct redirfs_cb_data_t data;
	int idx = 0;
	int inc_op = 0;
	void ***pre_ops;
	void ***post_ops;


	redirfs_debug("started");

	if (!filter || !ops)
		return -EINVAL;

	flt = redirfs_uncover_flt(filter);

	while (ops[idx].type != REDIRFS_END) {
		int type = ops[idx].type;
		int op = ops[idx].op;


		if (!ops[idx].pre_op && !ops[idx].post_op) {
			idx++;
			continue;
		}

		spin_lock(&flt->lock);

		pre_ops = redirfs_gettype(type, &flt->pre_ops);
		post_ops = redirfs_gettype(type, &flt->post_ops);

		if (ops[idx].pre_op) {
			if (!*pre_ops[op])
				inc_op += 1;

			*pre_ops[op] = (void*)ops[idx].pre_op;
		}
		
		if (ops[idx].post_op) {
			if (!*post_ops[op])
				inc_op += 1;

			*post_ops[op] = (void*)ops[idx].post_op;
		}

		spin_unlock(&flt->lock);
		
		data.flt = flt;
		data.i_val = inc_op;
		data.type = type;
		data.op = op;

		if (inc_op)
			redirfs_walk_roots(NULL, redirfs_set_flt_ops, &data);

		idx++;
	}

	redirfs_debug("ended");

	return 0;
}

int redirfs_remove_operations(redirfs_filter filter, struct redirfs_op_t ops[])
{
	struct redirfs_flt_t *flt;
	struct redirfs_cb_data_t data;
	int idx = 0;
	int dec_op = 0;
	void ***pre_ops;
	void ***post_ops;


	redirfs_debug("started");

	if (!filter || !ops)
		return -EINVAL;

	flt = redirfs_uncover_flt(filter);
	
	while (ops[idx].type != REDIRFS_END) {
		int type = ops[idx].type;
		int op = ops[idx].op;

		
		spin_lock(&flt->lock);

		pre_ops = redirfs_gettype(type, &flt->pre_ops);
		post_ops = redirfs_gettype(type, &flt->post_ops);

		if (!*pre_ops[op] && !*post_ops[op]) {
			idx++;
			continue;
		}

		if (!ops[idx].pre_op && *pre_ops[op]) {
			*pre_ops[op] = NULL;
			dec_op += 1;
		}

		if (!ops[idx].post_op && *post_ops[op]) {
			*post_ops[op] = NULL;
			dec_op += 1;
		}

		data.flt = flt;
		data.i_val = dec_op;
		data.type = type;
		data.op = op;

		spin_unlock(&flt->lock);

		if (dec_op)
			redirfs_walk_roots(NULL, redirfs_remove_flt_ops, &data);

	}

	redirfs_debug("ended");

	return 0;
}

EXPORT_SYMBOL(redirfs_set_operations);
EXPORT_SYMBOL(redirfs_remove_operations);
