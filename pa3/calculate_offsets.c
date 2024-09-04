#include <stddef.h>
#include <stdio.h>

typedef struct node {
    char *id;              // Pointer to string (8 bytes on 64-bit systems)
    unsigned long height;  // 64-bit unsigned integer (8 bytes)
    unsigned long xcoord;  // 64-bit unsigned integer (8 bytes)
    unsigned long ycoord;  // 64-bit unsigned integer (8 bytes)
    struct node *next;     // Pointer to the next node (8 bytes on 64-bit systems)
} node;

int main() {
    size_t id_offset = offsetof(node, id);
    size_t height_offset = offsetof(node, height);
    size_t xcoord_offset = offsetof(node, xcoord);
    size_t ycoord_offset = offsetof(node, ycoord);
    size_t next_offset = offsetof(node, next);
    size_t struct_size = sizeof(node);

    // Print the offsets and size
    printf(".equ NODE_ID_OFFSET,     %zu\n", id_offset);
    printf(".equ NODE_HEIGHT_OFFSET, %zu\n", height_offset);
    printf(".equ NODE_XCOORD_OFFSET, %zu\n", xcoord_offset);
    printf(".equ NODE_YCOORD_OFFSET, %zu\n", ycoord_offset);
    printf(".equ NODE_NEXT_OFFSET,   %zu\n", next_offset);
    printf(".equ NODE_STRUCT_SIZE,   %zu\n", struct_size);

    // Calculate the padding offset if it exists
    size_t expected_size = next_offset + sizeof(void *);
    size_t pad_offset = (expected_size < struct_size) ? expected_size : struct_size;

    if (pad_offset < struct_size) {
        printf(".equ NODE_PAD_OFFSET,   %zu\n", pad_offset);
    } else {
        printf(".equ NODE_PAD_OFFSET,   %zu\n", struct_size); // No padding if struct_size matches expected_size
    }

    return 0;
}
