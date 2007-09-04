#include "redir.h"

struct ops *ops_alloc(void)
{
	struct ops *ops;
	char *arr;

	ops = kmalloc(sizeof(struct ops), GFP_KERNEL);
	arr = kmalloc(sizeof(char) * RFS_OP_END, GFP_KERNEL);

	if (!ops || !arr) {
		kfree(ops);
		kfree(arr);
		return ERR_PTR(-ENOMEM);
	}

	memset(arr, 0, sizeof(char) * RFS_OP_END);
	ops->o_ops = arr;
	ops->o_count = 1;
	spin_lock_init(&ops->o_lock);

	return ops;
}

struct ops *ops_get(struct ops *ops)
{
	unsigned long flags;

	if (!ops || IS_ERR(ops))
		return NULL;

	spin_lock_irqsave(&ops->o_lock, flags);
	BUG_ON(!ops->o_count);
	ops->o_count++;
	spin_unlock_irqrestore(&ops->o_lock, flags);

	return ops;
}

void ops_put(struct ops *ops)
{
	unsigned long flags;
	int del = 0;

	if (!ops || IS_ERR(ops))
		return;

	spin_lock_irqsave(&ops->o_lock, flags);
	BUG_ON(!ops->o_count);
	ops->o_count--;
	if (!ops->o_count)
		del = 1;
	spin_unlock_irqrestore(&ops->o_lock, flags);

	if (!del)
		return;

	kfree(ops->o_ops);
	kfree(ops);
}