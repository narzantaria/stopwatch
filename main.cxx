#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Text_Display.H>
#include <iostream>
#include <vector>

Fl_Window *window;
Fl_Output *timeOutput;
Fl_Button *startButton;
Fl_Button *pauseButton;
Fl_Button *resetButton;
Fl_Text_Display *timeText;

bool isRunning = false;
int milliseconds = 0;
int seconds = 0;
int minutes = 0;
int hours = 0;

void updateTimeOutput()
{
  char str[12];
  std::snprintf(str, sizeof(str) + 1, "%02d:%02d:%02d.%03d", hours, minutes, seconds, milliseconds);
  timeOutput->value(str);
  window->redraw();
}

void timerCallback(void *)
{
  if (isRunning)
  {
    milliseconds += 10;
    if (milliseconds >= 1000)
    {
      milliseconds = 0;
      seconds++;
      if (seconds >= 60)
      {
        seconds = 0;
        minutes++;
        if (minutes >= 60)
        {
          minutes = 0;
          hours++;
        }
      }
    }
    updateTimeOutput();
    Fl::repeat_timeout(0.01, timerCallback);
  }
}

void startButtonCallback(Fl_Widget *, void *)
{
  isRunning = true;
  Fl::repeat_timeout(0.01, timerCallback);
}

void pauseButtonCallback(Fl_Widget *, void *)
{
  isRunning = false;
}

void resetButtonCallback(Fl_Widget *, void *)
{
  isRunning = false;
  milliseconds = 0;
  seconds = 0;
  minutes = 0;
  hours = 0;
  updateTimeOutput();
}

int main()
{
  window = new Fl_Window(300, 200);

  timeOutput = new Fl_Output(20, 20, 260, 50);
  timeOutput->value("00:00:00.000");
  timeOutput->textsize(30);
  timeOutput->textfont(FL_BOLD + FL_ITALIC);

  startButton = new Fl_Button(20, 100, 80, 30, "Start");
  pauseButton = new Fl_Button(110, 100, 80, 30, "Pause");
  resetButton = new Fl_Button(200, 100, 80, 30, "Reset");

  startButton->callback(startButtonCallback);
  pauseButton->callback(pauseButtonCallback);
  resetButton->callback(resetButtonCallback);

  window->end();
  window->show();
  return Fl::run();
}