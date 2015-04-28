#include <stdio.h>
#include <inttypes.h>
#include "read_tree.h"

int main(void) {
  
  long long index = 0;
  long long halo_index = 0;
  read_tree("/Users/y1275963/ass3/data/tree_0_0_0.dat");
    
  printf("number of halos: %llu\n", all_halos.num_halos);
  printf("number of lists %llu\n", halo_tree.num_lists);
  printf("num of scales %llu\n",halo_tree.num_scales);
  for(index = 0;index<halo_tree.num_lists;index++){
        printf("sclae factor canv: %llu\n",halo_tree.scale_factor_conv[index]);
  }
  
  for(index = 0;index <halo_tree.num_lists;index++){
        float temp = halo_tree.halo_lists[index].scale;
        int id = halo_tree.halo_lists[index].halo_lookup->id;
        int ind = halo_tree.halo_lists[index].halo_lookup->index;        
        printf("current list: scale:%f ->id:%d -> index :%d\n",temp,id,ind);
        for(halo_index = 0 ;halo_index<halo_tree.halo_lists[index].num_halos; halo_index ++){
                struct halo temp = halo_tree.halo_lists[index].halos[halo_index];
                printf("current halo: \t scale: %f, id : %llu\n",temp.scale,temp.id);
                if(temp.parent != NULL)
                        printf("\t \t its parent: scale: %f, id : %llu\n",temp.parent->scale,temp.parent->id);
                if(temp.desc != NULL)
                        printf("\t \t its decs: scale: %f, id : %llu\n",temp.desc->scale,temp.desc->id);
                        
        }
  }

  return 0;
}
