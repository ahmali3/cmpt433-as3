#define _DEFAULT_SOURCE
#include "joystick.h"

// Joystick files
#define JSUP "/sys/class/gpio/gpio26/value"
#define JSDOWN "/sys/class/gpio/gpio46/value"
#define JSLEFT "/sys/class/gpio/gpio65/value"
#define JSRIGHT "/sys/class/gpio/gpio47/value"
#define JSIN "/sys/class/gpio/gpio27/value"

enum joystickDir
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    IN,
    UNPRESSED
};

static void runCommand(char *command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe))
    {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
        // printf("--> %s", buffer); // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0)
    {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

void initJoystick(void)
{
    runCommand("config-pin p8.14 gpio");
    runCommand("config-pin p8.15 gpio");
    runCommand("config-pin p8.16 gpio");
    runCommand("config-pin p8.18 gpio");
    runCommand("config-pin p8.17 gpio");
    runCommand("echo in > /sys/class/gpio/gpio26/direction");
    runCommand("echo in > /sys/class/gpio/gpio46/direction");
    runCommand("echo in > /sys/class/gpio/gpio65/direction");
    runCommand("echo in > /sys/class/gpio/gpio47/direction");
    runCommand("echo in > /sys/class/gpio/gpio27/direction");
}

enum joystickDir readJoystick(void)
{
    FILE *fp;
    char buffer[10];
    int up, down, left, right, in;
    fp = fopen(JSUP, "r");
    fgets(buffer, 10, fp);
    up = atoi(buffer);
    fclose(fp);
    fp = fopen(JSDOWN, "r");
    fgets(buffer, 10, fp);
    down = atoi(buffer);
    fclose(fp);
    fp = fopen(JSLEFT, "r");
    fgets(buffer, 10, fp);
    left = atoi(buffer);
    fclose(fp);
    fp = fopen(JSRIGHT, "r");
    fgets(buffer, 10, fp);
    right = atoi(buffer);
    fclose(fp);
    fp = fopen(JSIN, "r");
    fgets(buffer, 10, fp);
    in = atoi(buffer);
    fclose(fp);

    if (up == 0)
    {
        return UP;
    }
    else if (down == 0)
    {
        return DOWN;
    }
    else if (left == 0)
    {
        return LEFT;
    }
    else if (right == 0)
    {
        return RIGHT;
    }
    else if (in == 0)
    {
        return IN;
    }
    else
    {
        return UNPRESSED;
    }
}

void controlAudio(void)
{
    if (readJoystick() == UP)
    {
        while (1)
        {
            if (readJoystick() != UP)
            {
                AudioMixer_setVolume(AudioMixer_getVolume() + 5);
                usleep(1000);
                break;
            }
        }
    }
    else if (readJoystick() == DOWN)
    {
        while (1)
        {
            if (readJoystick() != DOWN)
            {
                AudioMixer_setVolume(AudioMixer_getVolume() - 5);
                usleep(1000);
                break;
            }
        }
    }
    else if (readJoystick() == LEFT)
    {
        while (1)
        {
            if (readJoystick() != LEFT)
            {
                setBpm(getBpm() - 5);
                usleep(1000);
                break;
            }
        }
    }
    else if (readJoystick() == RIGHT)
    {
        while (1)
        {
            if (readJoystick() != RIGHT)
            {
                setBpm(getBpm() + 5);
                usleep(1000);
                break;
            }
        }
    }
    else if (readJoystick() == IN)
    {
        while (1)
        {
            if (readJoystick() != IN)
            {
                setAudioMode((getAudioMode() + 1) % 3);
                usleep(1000);
                break;
            }
        }
    }
}

void *joystickThread(void *arg)
{
    initJoystick();
    while (1)
    {
        controlAudio();
    }
    return NULL;
}

void startJoystickThread(pthread_t *thread)
{
    pthread_create(thread, NULL, joystickThread, NULL);
}
