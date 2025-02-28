#include "Task.h"

void Complue(Car *car)
{
  // µ×ÅÌ¼ÆËã
  MG513_Calculate(&car->motorgroup[0]->pid1, car->motorgroup[0]->cout);
  MG513_Calculate(&car->motorgroup[1]->pid1, car->motorgroup[1]->cout);
  //
  pids *temp_pid[4] = {NULL};
  for (int i = 0; i < 4; i++)
  {
    temp_pid[i] = &car->motorgroup[i]->pid1;
  }
  MG513_pwm_send(temp_pid);
}

void Remate_Control()
{
}
