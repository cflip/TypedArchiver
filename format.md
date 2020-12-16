# TAF (Typed Archive Format) Specification

## Blocks
Data is stored in blocks of data with a header

### Block types
- List: A list of blocks similar to a directory in a file structure.
- String: A simple string of text
- Image: Raw RGB image data.

### Header
- Name: 16 bytes
- Block type: 1 byte
- Block size: 4 bytes
- Date: 4 bytes

The number of bytes of data that follow the header is specified in the block size from the header.