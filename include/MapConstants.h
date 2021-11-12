/* Gonna share this with the ``main'' program, so I might as well put this in a
 separate file */
/* map specific constants */
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NUMBER_OF_MAP_TYPES 3
#define NUMBER_OF_GRD_TEXTURES 6

const char texture_names[3][50] = {"%spradaria%d.png",
                                   "%sdeserto%d.png",
				   "%sneve%d.png"};
#endif /* CONSTANTS_H */
