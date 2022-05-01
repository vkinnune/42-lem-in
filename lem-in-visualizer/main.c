#include <raylib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define TIME_ANT_IS_MOVING 0.75f
#define BYTES_PER_READ 64
#define NAME_LENGTH 64
#define FPS 60
#define FRAMES_PER_TICK 60

void
crash(char* p)
{
    printf("%s\n", p);
    exit(-1);
}

int
main()
{
    //read
    size_t text_size = 0;
    char* p_text = NULL;
    {
        size_t allocated = BYTES_PER_READ;
        p_text = malloc(allocated);
        size_t read_bytes;
        while(1)
        {
            read_bytes = read(0, p_text + text_size, BYTES_PER_READ);
            if(read_bytes == 0) break; //EOF
            text_size += read_bytes;
            if(text_size + BYTES_PER_READ > allocated)
            {
                allocated += BYTES_PER_READ;
                p_text = realloc(p_text, allocated);
            }
        }
        printf("%lu chars read\n", text_size);
    }


    //parse
    size_t ant_count;

    int start_index;
    int end_index;
    char* p_room_names; //use NAME_LENGTH for stride
    int* p_room_xs;
    int* p_room_ys;
    size_t room_count;

    int* p_links; // ints in pairs. to and from. (ints are indexes to rooms)
    size_t links_count;

    int* p_ant_x_ticks; // array with size tick_count made up of arrays with size ant_count.
    int* p_ant_y_ticks; //  ant_count is stride
    size_t tick_count;
    {
        char* p = p_text;
        //ant count
        ant_count = 0;
        while(1)
        {
            if(*p == '#')
            {
               while(*p != '\n') p++;
               p++;
               continue;
            }
            while(*p >= '0' && *p <= '9')
            {
                ant_count = ant_count * 10;
                ant_count = ant_count + (*p - '0');
                p++;
            }
            if(*p == '\n') 
            {
                p++;
                break;
            }
            crash("Error: ant count");
        }

        //rooms
        room_count = 0;
        size_t room_allocated = 0;
        p_room_names = NULL;
        p_room_xs = NULL;
        p_room_ys = NULL;
        while(1)
        {
            assert(p[-1] == '\n');
            //#
            if(*p == '#')
            {
                if(p[1] == '#')
                {
                    if(0 == strncmp(p, "##start", 7))
                    {
                        start_index = room_count;
                        printf("start: %d\n", start_index);
                    }
                    else if(0 == strncmp(p, "##end", 5))
                    {
                        end_index = room_count;
                        printf("end: %d\n", end_index);
                    }
                }
                while(*p != '\n') p++;
                p++;
                continue;
            }

            //realloc
            if(room_allocated <= room_count+1)
            {
                room_allocated += 2; //todo times two
                p_room_names = realloc(p_room_names, room_allocated * NAME_LENGTH);
                p_room_xs = realloc(p_room_xs, room_allocated * sizeof(int));
                p_room_ys = realloc(p_room_ys, room_allocated * sizeof(int));
            }

            //room name
            int i = 0;
            char* start_of_line = p;
            while(1)
            {
                if(*p == '-') //end of rooms, start of links.
                {
                    p = start_of_line;
                    break;
                }
                if(*p == '\n') crash("Error: bad room name");
                if(i+1 >= NAME_LENGTH) crash("Error: too long room name");
                if(*p == ' ') //this allows blank names
                {
                    p_room_names[room_count * NAME_LENGTH + i] = '\0';
                    printf("Room %lu: %s\n", room_count, p_room_names + (room_count * NAME_LENGTH));
                    p++;
                    break;
                }
                p_room_names[room_count * NAME_LENGTH + i] = *p;
                p++;
                i++;
            }
            if(p == start_of_line) break; //end of rooms start of links

            //room x
            if(*p >= '0' && *p <= '9')
            {
                int x = 0;
                while(*p >= '0' && *p <= '9')
                {
                    x *= 10;
                    x += *p - '0';
                    p++;
                }
                p_room_xs[room_count] = x;
            }
            else crash("Error: room x");
            if(*p != ' ') crash("Error: room xy seperator is not space");
            p++;

            //room y
            if(*p >= '0' && *p <= '9')
            {
                int y = 0;
                while(*p >= '0' && *p <= '9')
                {
                    y *= 10;
                    y += *p - '0';
                    p++;
                }
                p_room_ys[room_count] = y;
            }
            else crash("Error: room y");
            if(*p != '\n') crash("Error: room doesnt end in '\\n'");
            room_count++;
            p++;
        }
        //rooms

        //links
        /* links skip!:
        {
            while(!(*p == 'L' && p[-1] == '\n')) p++;
        }
        */
        p_links = NULL; // ints in pairs. to and from. (indexes to rooms)
        links_count = 0;

        size_t links_allocated = 0;
        char seperator = '-';
        int match;
        while(1)
        {
            match = -1;
            if(links_count == links_allocated)
            {
                links_allocated += 2;
                p_links = realloc(p_links, sizeof(int) * 2 * links_allocated);
            }
            size_t number = p - p_text;
            if(number >= text_size)
            {
               printf("Read %li bytes over text\l", (long int)number - (long int)text_size);
               break;
            }
            if(*p == '#')
            {
                while(*p != '\n') p++;
                p++;
                continue;
            }
            for(int i = 0; i < room_count; i++)
            {
                int ci = 0;
                while(p_room_names[i*NAME_LENGTH + ci] == p[ci]) ci++;
                if(p_room_names[i*NAME_LENGTH + ci] == '\0' && p[ci] == seperator)
                {
                    match = i;
                    p += ci;
                    p++; //skips seperator
                    break;
                }
            }
            if(match == -1) 
                crash("Error: link name not found");
            if(seperator == '-')
            {
                p_links[links_count*2] = match;
                seperator = '\n';
                continue;
            }
            else if(seperator == '\n')
            {
                p_links[links_count*2 + 1] = match;
                links_count++;
                if(*p == '\n') //double nl is end of links
                {
                    p++; //skip to expected L
                    break;
                }
                seperator = '-';
                continue;
            }
            crash("Error: links\n");
        }
        //links

        //ant ticks
        size_t tick_allocation = 8;
        tick_count = 1;
        p_ant_x_ticks = malloc(sizeof(int) * ant_count * tick_allocation);
        p_ant_y_ticks = malloc(sizeof(int) * ant_count * tick_allocation);
        //starting position
        for(int ant = 0; ant < ant_count; ant++)
        {
            p_ant_x_ticks[ant] = p_room_xs[start_index];
            p_ant_y_ticks[ant] = p_room_ys[start_index];
        }
        {
            size_t ant;
            int nl_detected = 1;
            while(1)
            {
                if(*p != 'L') //L is expected
                {
                    if(*p == '\n' || *p == 0) break; //todo think about this
                    printf("\n%c", *p);
                    crash("-badword\n");
                }
                p++;
                if(tick_allocation <= tick_count + 1)
                {
                    tick_allocation += 2;
                    p_ant_x_ticks = realloc(p_ant_x_ticks, sizeof(int) * ant_count * tick_allocation);
                    p_ant_y_ticks = realloc(p_ant_y_ticks, sizeof(int) * ant_count * tick_allocation);
                }
                //set new tick positions same as the tick before
                for(int i = 0; nl_detected && (i < ant_count); i++)
                {
                    size_t offset = (ant_count * tick_count) + i;
                    p_ant_x_ticks[offset] = p_ant_x_ticks[offset - ant_count];
                    p_ant_y_ticks[offset] = p_ant_y_ticks[offset - ant_count];
                }
                if(*p >= '0' && *p <= '9')
                {
                    ant = 0;
                    while(*p >= '0' && *p <= '9')
                    {
                        ant *= 10;
                        ant += *p - '0';
                        p++;
                    }
                    ant--; //input ant numbers start with 1
                }
                else crash("Error: ant number");
                if(*p != '-') crash("Error: ant seperator");
                p++;

                //find mathing name by index
                nl_detected = 0;

                int match = -1;
                int n = 0;
                int i = 0;
                while(i < room_count)
                {
                    if(p_room_names[i * NAME_LENGTH + n] == '\0')
                    {
                        if(p[n] == '\n')
                        {
                            match = i;
                            nl_detected = 1;
                            //printf("Newline\n");
                            p += n;
                            break;
                        }
                        else if(p[n] == ' ')
                        {
                            match = i;
                            //printf("Space\n");
                            p += n;
                            break;
                        }
                    }
                    if(p_room_names[i * NAME_LENGTH + n] != p[n])
                    {
                        //printf("Mismatch (%d): '%s', '%s'\n", n, p_room_names + (i * NAME_LENGTH), p);
                        n = 0;
                        i++;
                        continue;
                    }
                    else 
                    {
                        n++;
                        continue;
                    }
                    crash("Error: impossible\n");
                }
                if(match == -1) crash("Error: instruction bad name");
                p_ant_x_ticks[tick_count * ant_count + ant] = p_room_xs[match];
                p_ant_y_ticks[tick_count * ant_count + ant] = p_room_ys[match];
                tick_count += nl_detected;
                if(*p != ' ' && *p != '\n') crash("Error: expected \\n or space");
                p++;
            }
        }
        //ant ticks
        printf("%lu animation ticks!\n", tick_count);
    }
    //raylib window creation and drawing
    {
        int win_x;
        int win_y;
        size_t frame = 0;

        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
        InitWindow(0, 0, "lem-in visualizer");
        SetTargetFPS(FPS);

        //viewbox
        int max_x = p_room_xs[0];
        int min_x = p_room_xs[0];
        int max_y = p_room_ys[0];
        int min_y = p_room_ys[0];
        {
            for(int i = 0; i < room_count; i++)
            {
                int x, y;
                x = p_room_xs[i];
                y = p_room_ys[i];
                if(x > max_x) max_x = x;
                if(x < min_x) min_x = x;
                if(y > max_y) max_y = y;
                if(y < min_y) min_y = y;
            }
            //TODO: fix margins so its in pixel space
            max_x += 2;
            max_y += 2;
            min_x -= 2;
            min_y -= 2;
        }
        printf("x: max: %d, min: %d\ny: max: %d, min: %d\n", max_x, min_x, max_y, min_y);

        while (!WindowShouldClose())
        {
            win_x = GetScreenWidth();
            win_y = GetScreenHeight();

            //offset and zoom
            //offset is in pixels
            int offset_x;
            int offset_y;
            float zoom;
            {
                float win_ratio = (float)win_x / (float)win_y;
                float viewbox_ratio = (float)(max_x - min_x) / (float)(max_y - min_y);
                if(win_ratio > viewbox_ratio)
                {
                    zoom = (float)win_y / (float)(max_y - min_y);
                }
                else
                {
                    zoom = (float)win_x / (float)(max_x - min_x);
                }
                offset_x = -(int)((float)min_x * zoom);
                offset_y = -(int)((float)min_y * zoom);
            }

            BeginDrawing();
            {
                Color bg_color = {45, 45, 45, 255};
                ClearBackground(bg_color);
                //DrawFPS(0, 0);
                //draw links
                {
                    Vector2 from, to;
                    for(int i = 0; i < links_count; i++)
                    {
                        from.x = (float) p_room_xs[p_links[i*2]] * zoom + (float)offset_x;
                        from.y = (float) p_room_ys[p_links[i*2]] * zoom + (float)offset_y;
                        to.x = (float) p_room_xs[p_links[i*2 + 1]] * zoom + (float)offset_x;
                        to.y = (float) p_room_ys[p_links[i*2 + 1]] * zoom + (float)offset_y;
                        //printf("link: %d from: %f %f\n to: %f %f\n", i, from.x, from.y, to.x, to.y);

                        DrawLineEx(from, to, 0.12f * zoom, LIGHTGRAY);
                    }
                }

                //draw rooms
                {
                    int x;
                    int y;
                    Color color;
                    for(int i = 0; i < room_count; i++)
                    {
                        int size_x = (int)(0.25f*zoom);
                        int size_y = (int)(0.25f*zoom);
                        x = offset_x - (size_x/2) + (int)(zoom * (float)p_room_xs[i]);
                        y = offset_y - (size_y/2) + (int)(zoom * (float)p_room_ys[i]);
                        color = GRAY;
                        if(i == start_index) color = DARKBLUE;
                        if(i == end_index) color = MAROON;
                        DrawRectangle(x, y, size_x, size_y, color);
                    }
                }
                //draw ants
                {
                    int x;
                    int y;
                    int next_x;
                    int next_y;
                    float lerp;
                    int n;

                    lerp = (((float)(frame % ((size_t)FRAMES_PER_TICK))) / (float)FRAMES_PER_TICK)  / (float)TIME_ANT_IS_MOVING;
                    if(lerp > 1.0f) lerp = 1.0f;
                    size_t anim_tick = (frame % ((size_t)tick_count * (size_t)FRAMES_PER_TICK)) / ((size_t)FRAMES_PER_TICK);
                    {
                        char* p_c = malloc(2);
                        p_c[0] = '0' + anim_tick;
                        p_c[1] = '\0';
                        DrawText((const char*)p_c, 15, 5, 64, RAYWHITE);
                        free(p_c);
                    }
                    for(size_t i = 0; i < ant_count; i++)
                    {
                        n = anim_tick*ant_count + i;
                        x = offset_x + (int)(zoom * (float)p_ant_x_ticks[n]);
                        y = offset_y + (int)(zoom * (float)p_ant_y_ticks[n]);
                        n = (1+anim_tick) * ant_count + i;
                        //dont interpolate after last frame
                        if(anim_tick < tick_count-1) next_x = offset_x + (int)(zoom * (float)p_ant_x_ticks[n]);
                        else next_x = x;
                        if(anim_tick < tick_count-1) next_y = offset_y + (int)(zoom * (float)p_ant_y_ticks[n]);
                        else next_y = y;

                        x = x + (int)(((float)next_x - (float)x) * lerp);
                        y = y + (int)(((float)next_y - (float)y) * lerp);
                        DrawCircle(x, y, 0.2f*zoom, (Color){20, 15, 15, 215});
                    }

                    //draw room names
                    for(int i = 0; i < room_count; i++)
                    {
                        int size = (int)(zoom*0.45f);
                        int x = p_room_xs[i] * zoom + offset_x - (MeasureText((const char*)(p_room_names + i*NAME_LENGTH), size)/2);
                        int y = p_room_ys[i] * zoom + offset_y - (int)((float)size*1.5f);
                        DrawText((const char*)(p_room_names + i*NAME_LENGTH), x, y, size, RED);
                    }
                }
            }
            EndDrawing();
            frame++;
        }
        // window closed
    }
    return 0;
}
