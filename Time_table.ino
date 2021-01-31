const int table_timer_start[] = {
  20,
  25,
  19,
  05
  }
;

const int table_timer_finish[] = {
  20,
  50,
  19,
  25
}
;

int Timer_Table() {
  int i = 0;
  boolean relay_status = false;
  while (i <= (sizeof(table_timer_start) / sizeof(int)) / 2) {
    int timer_start = (table_timer_start[i] * 3600) + (table_timer_start[i + 1] * 60);
    int timer_finish = (table_timer_finish[i] * 3600) + (table_timer_finish[i + 1] * 60);
    if ((hour * 3600) + (minute * 60) >= timer_start && (hour * 3600) + (minute * 60) <= timer_finish) {
      relay_status = true;
      i = -500;
    }
    i = i + 2;
  }
  return relay_status;
}
