#**Data Compression – Huffman Coding**

Use **Huffman coding** to compress a given input file, send the stream of characters as packets to a receiver, stimulating noise in the channel, and finally decode the data at the receiver end. 

> - Study the probability of occurrence of unique symbols in arbitrarily large text data and compute the **entropy**. 
> - Source code the data using **Huffman coding** algorithm and generate a code book  for the symbols in the text data . 
> - Divide the data into packets of some fixed length(7 in our case) and channel encode each packet . 
> - Assume some arbitrary bit rate error and generate bit errors in each packet .
> - Use the client server programs provided to send the signal across the channel.
> - Recover the text from the received data and check whether there is an error or not by using the **Cyclic Redundancy Check(CRC)** and request for a re­transmission if it has an error . We do so until we generate the same text data as the input file . 				

*Check the report for detailed observations and inferences.*