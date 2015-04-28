#include <stdio.h>
#include <inttypes.h>
#include "read_tree.h"

int main(void) {
  
  long long index = 0;
  long long halo_index = 0;
  read_tree("/Users/y1275963/ass3/data/tree_0_0_0.dat");
  
  index = 0;

  for(halo_index = 0 ;halo_index < halo_tree.halo_lists[index].num_halos; halo_index ++){
  		struct halo temp = halo_tree.halo_lists[index].halos[halo_index];  
  		printf("%llu,%f,%f,%f,%f\n",temp.id,temp.rvir,temp.pos[0],temp.pos[1],temp.pos[2]);
    }
  return 0;
}
