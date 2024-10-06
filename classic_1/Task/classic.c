#include "classic.h"

extern CLASSIC group1;

void Classic_task(void) {
  // valve_change(&callback, &group1);
  //  if (group1.V_goal[0] == NULL && group1.V_goal[1] == NULL && group1.V_goal[2] == NULL
  //      && group1.V_goal[3] == NULL) {
  //    //    for (int i = 0; i < 2; i++) {
  //    //      group1.V_goal[i] = 2000;
  //    //    }
  //  }
  Action_solution(&group1, 1, 2000, 0, 0);

  Action_solution(&group1, 0, 2000, 0, 0);
}
