// Annottaion for maple tree tracing

#undef TRACE_SYSTEM
#define TRACE_SYSTEM maple_tree

#if !defined(_TRACE_MM_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MM_H

#include <linux/tracepoint.h>

struct ma_state;

// Defines three trace events that can be hooked into the kernel's ftrace system to observe Maple Tree operations at runtime:
	// ma_op - Tracks general operations on the tree
	// ma_read - Tracks read operations
	// ma_write - Tracks write operations — additionally tracks piv (pivot) and val (value being written)


// The function trace_ma_op() triggers this event
TRACE_EVENT(ma_op,

	TP_PROTO(const char *fn, struct ma_state *mas),

	TP_ARGS(fn, mas),

	TP_STRUCT__entry(
			__field(const char *, fn)
			__field(unsigned long, min)
			__field(unsigned long, max)
			__field(unsigned long, index)
			__field(unsigned long, last)
			__field(void *, node)
	),

	TP_fast_assign(
			__entry->fn		= fn;
			__entry->min		= mas->min;
			__entry->max		= mas->max;
			__entry->index		= mas->index;
			__entry->last		= mas->last;
			__entry->node		= mas->node;
	),

	TP_printk("%s\tNode: %p (%lu %lu) range: %lu-%lu",
		  __entry->fn,
		  (void *) __entry->node,
		  (unsigned long) __entry->min,
		  (unsigned long) __entry->max,
		  (unsigned long) __entry->index,
		  (unsigned long) __entry->last
	)
)

// The function trace_ma_read() triggers this event
TRACE_EVENT(ma_read,

	TP_PROTO(const char *fn, struct ma_state *mas),

	TP_ARGS(fn, mas),

	TP_STRUCT__entry(
			__field(const char *, fn)
			__field(unsigned long, min)
			__field(unsigned long, max)
			__field(unsigned long, index)
			__field(unsigned long, last)
			__field(void *, node)
	),

	TP_fast_assign(
			__entry->fn		= fn;
			__entry->min		= mas->min;
			__entry->max		= mas->max;
			__entry->index		= mas->index;
			__entry->last		= mas->last;
			__entry->node		= mas->node;
	),

	TP_printk("%s\tNode: %p (%lu %lu) range: %lu-%lu",
		  __entry->fn,
		  (void *) __entry->node,
		  (unsigned long) __entry->min,
		  (unsigned long) __entry->max,
		  (unsigned long) __entry->index,
		  (unsigned long) __entry->last
	)
)

// The function trace_ma_write() triggers this event
TRACE_EVENT(ma_write,

	// TP_PROTO shows what parameters the trace point accepts
	TP_PROTO(const char *fn, struct ma_state *mas, unsigned long piv,
		 void *val),

	// TP_ARGS defines the arguments
	TP_ARGS(fn, mas, piv, val),

	// TP_STRUCT__entry defines what data to capture and store
	TP_STRUCT__entry(
			__field(const char *, fn)
			__field(unsigned long, min)
			__field(unsigned long, max)
			__field(unsigned long, index)
			__field(unsigned long, last)
			__field(unsigned long, piv)
			__field(void *, val)
			__field(void *, node)
	),

	// Copies the data from mas and then stores it in a buffer awaiting usage in TP_printk
	TP_fast_assign(
			__entry->fn		= fn;
			__entry->min		= mas->min;
			__entry->max		= mas->max;
			__entry->index		= mas->index;
			__entry->last		= mas->last;
			__entry->piv		= piv;
			__entry->val		= val;
			__entry->node		= mas->node;
	),

	// Prints out the logs
	TP_printk("%s\tNode %p (%lu %lu) range:%lu-%lu piv (%lu) val %p",
		  __entry->fn,
		  (void *) __entry->node,
		  (unsigned long) __entry->min,
		  (unsigned long) __entry->max,
		  (unsigned long) __entry->index,
		  (unsigned long) __entry->last,
		  (unsigned long) __entry->piv,
		  (void *) __entry->val
	)
)
#endif /* _TRACE_MM_H */

/* This part must be outside protection */
#include <trace/define_trace.h>