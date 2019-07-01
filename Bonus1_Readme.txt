Question:
=========
Which problem can occur if the content of the MDAT box is very large?

Answer:
=======
The size of the MDAT box will impact:
- the processing time : Very large files will take longer to be processed (challenging for video real time applications)
- the memory allocation : Depending on the chosen software architecture, if only one buffer is used to store the complete payload, very large files will be allowed large memory space

