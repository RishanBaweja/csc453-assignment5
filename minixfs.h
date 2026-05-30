#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Put shared structs and constants here */

#define SECTOR_SIZE 512
#define PART_TABLE_OFFSET 0x1BE   /* location of the partition table */
#define PART_TABLE_MAGIC_1 0x55   /* byte 510 boot sect w/ valid part table */
#define PART_TABLE_MAGIC_2 0xAA   /* byte 511 boot sect w/ valid part table */
#define MINIX_PARTITION_TYPE 0x81 /* partition type for Minix */
#define MINIX_MAGIC 0x4D5A        /* the minix magic number */
#define MINIX_MAGIC_REVERSED      /* minix magic num on byte-reversed fs */
#define INODE_SIZE 64
#define DIRENT_SIZE 64
#define ROOT_INODE 1
#define DIRECT_ZONES 7


#define FILE_TYPE_MASK 0170000
#define REGULAR_FILE   0100000
#define DIRECTORY_FILE 0040000

struct partition_table {
  uint8_t bootind; /* Boot magic number (0x80 if bootable) */
  uint8_t start_head; /* Start of partition in CHS */
  uint8_t start_sec;
  uint8_t start_cyl;
  uint8_t type; /* Type of partition (0x81 is minix) */
  uint8_t end_head; /* End of partition in CHS */
  uint8_t end_sec;
  uint8_t end_cyl;
  uint32_t lFirst; /* First sector (LBA addressing) */
  uint32_t size;
};

struct superblock {
  /* Minix Version 3 Superblock
  * this structure found in fs/super.h
  * in minix 3.1.1 */

  /* on disk. These fields and orientation are non–negotiable */
  uint32_t ninodes; /* number of inodes in this filesystem */
  uint16_t pad1; /* make things line up properly */
  int16_t i_blocks; /* # of blocks used by inode bit map */
  int16_t z_blocks; /* # of blocks used by zone bit map */
  uint16_t firstdata; /* number of first data zone */
  int16_t log_zone_size; /* log2 of blocks per zone */
  int16_t pad2; /* make things line up again */
  uint32_t max_file; /* maximum file size */
  uint32_t zones; /* number of zones on disk */
  int16_t magic; /* magic number */
  int16_t pad3; /* make things line up again */
  uint16_t blocksize; /* block size in bytes */
  uint8_t subversion; /* filesystem sub–version */
};

struct inode {
  uint16_t mode; /* mode */
  uint16_t links; /* number or links */
  uint16_t uid;
  uint16_t gid;
  uint32_t size;
  int32_t atime;
  int32_t mtime;
  int32_t ctime;
  uint32_t zone[DIRECT_ZONES];
  uint32_t indirect;
  uint32_t two_indirect;
  uint32_t unused;
};

struct min_dir_entry {
  uint32_t inode; /* inode number */
  unsigned char name[60];
};