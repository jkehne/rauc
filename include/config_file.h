#pragma once

#include <glib.h>

#include <checksum.h>

/* System configuration */
typedef struct {
	gchar *system_compatible;
	gchar *system_bootloader;
	/* path prefix where rauc may create mount directories */
	gchar *mount_prefix;

	gchar *keyring_path;

	GHashTable *slots;
} RaucConfig;

typedef enum {
	ST_UNKNOWN,
	ST_ACTIVE,
	ST_INACTIVE
} SlotState;

typedef struct _RaucSlot {
	/** name of the slot. A glib intern string. */
	const gchar *name;
	/** slot class the slot belongs to. A glib intern string. */
	const gchar *sclass;
	/** device this slot uses */
	gchar *device;
	/** the slots partition type */
	gchar *type;
	/** the name this slot is known to the bootloader */
	gchar *bootname;
	/** flag indicating if the slot is updatable */
	gboolean readonly;
	/** current state of the slot (runtime) */
	SlotState state;
	struct _RaucSlot *parent;
} RaucSlot;

typedef struct {
} RaucSlotGroup;

typedef struct {
	gchar *status;
	RaucChecksum checksum;
} RaucSlotStatus;

gboolean load_config(const gchar *filename, RaucConfig **config);
void free_config(RaucConfig *config);

gboolean load_slot_status(const gchar *filename, RaucSlotStatus **slotstatus);
gboolean save_slot_status(const gchar *filename, RaucSlotStatus *slotstatus);
void free_slot_status(RaucSlotStatus *slotstatus);
