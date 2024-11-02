// int width = 0;
// int height = 0;
// int pixel_size = 2;

// int buffer_size = display_buffer; 
// uint32_t *display_buffer_1;
// uint32_t *display_buffer_2;
// int lock1 = 1;
// int lock2 = 1;

// #define min(a,b) ((a)<(b)?(a):(b))
// #define max(a,b) ((a)>(b)?(a):(b))

// void rebuild_display_buffer()
// {
//     display_object_t *obj = NULL;
//     reset_Iterators();
//     while (1)
//     {
//        obj = display_Iterators();
//        if(obj == NULL) break;
//        if(width < obj->Offset_X +obj->object_data_t.object_width)
//             width = obj->Offset_X +obj->object_data_t.object_width;
//        if(height < obj->Offset_Y +obj->object_data_t.object_height)
//             height = obj->Offset_Y +obj->object_data_t.object_height;
//     }
// }


// void init_display_buffer()
// {
//      display_buffer_1 = (uint32_t *)malloc(sizeof(uint32_t)*buffer_size);
//      display_buffer_2 = (uint32_t *)malloc(sizeof(uint32_t)*buffer_size);
//      if(display_buffer_1 == NULL || display_buffer_2 == NULL)
//      {
//          printf("Memory allocation failed\n");
//          return;
//      }
//      memset(display_buffer_1, 0, sizeof(uint32_t)*buffer_size);
//      memset(display_buffer_2, 0, sizeof(uint32_t)*buffer_size);
//      rebuild_display_buffer();
// }

// void draw_display_buffer(int Offset_X, int Offset_Y, int width, int height,void *buffer,color_mode_t color_mode)
// {
//     /*获取显示缓冲区*/
//     uint32_t *this_display_buffer = NULL;
//     int use = 0;
//     while (1)
//     {
//        if(lock1 == 1)
//        {
//          lock1-- ;
//          this_display_buffer = display_buffer_1;
//          use = 1;
//          break;
//        }
//        if(lock2 == 1)
//        {
//          lock2-- ;
//          this_display_buffer = display_buffer_2;
//          use = 2;
//          break;
//        }
//     }


//     display_object_t *obj = NULL;

//     int x_coordanate = 0;
//     int y_coordinate = 0;
//     int x_coordinate_of_draw = 0;
//     int y_coordinate_of_draw = 0;
//     int width_offset_l = 0;
//     int height_offset_l = 0;
//     int draw_width;
//     int draw_height;
//     /*遍历显示对象*/
//     reset_Iterators();
//     while ((obj = display_Iterators())!= NULL)
//     {
//        if(obj == NULL) break;
//        if(obj->Offset_X+obj->object_data_t.object_width > Offset_X &&               //判断显示器绘制区域是否在显示对象范围内
//           obj->Offset_X < Offset_X+width && 
//           obj->Offset_Y+obj->object_data_t.object_height > Offset_Y && 
//           obj->Offset_Y < Offset_Y+height)
//           { 
//             /*计算矩形绘制区域在显示器坐标系中的坐标*/
//              x_coordanate = max(Offset_X - obj->Offset_X,0);
//              y_coordinate = max(Offset_Y - obj->Offset_Y,0);
//             /*计算矩形绘制区域在显示任务坐标系中的坐标*/
//             x_coordinate_of_draw = max(0,obj->Offset_X - Offset_X);
//             y_coordinate_of_draw = max(0,obj->Offset_Y - Offset_Y);   

//            /*计算矩形绘制区域的大小*/
//              width_offset_l = obj->Offset_X - Offset_X; 
//              height_offset_l = obj->Offset_Y - Offset_Y;  
//              if(width_offset_l > 0)                       //显示器绘制区域的宽度
//              { draw_width = width - width_offset_l;   
//                if(draw_width > obj->object_data_t.object_width)
//                draw_width = obj->object_data_t.object_width;
//              }
//              else
//              {
//                 if(width - width_offset_l >= obj->object_data_t.object_width)
//                 draw_width = obj->object_data_t.object_width + width_offset_l;
//                 else
//                 draw_width = width + width_offset_l;
//              }

//              if (height_offset_l > 0)                     //显示器绘制区域的高度
//              {
//                 draw_height = height - height_offset_l;
//                 if(draw_height > obj->object_data_t.object_height)
//                 draw_height = obj->object_data_t.object_height;
//              }
//              else
//              {
//                 if(height - height_offset_l >= obj->object_data_t.object_height)
//                 draw_height = obj->object_data_t.object_height + height_offset_l;
//                 else
//                 draw_height = height + height_offset_l;
//              }

//              /*构建显示缓冲区信息*/
//              int j = 0;                                //发送数据缓冲区指针，
//              int k = x_coordinate_of_draw + y_coordinate_of_draw * y_coordinate_of_draw;//接收数据指针
//              for(int i = 0; i < draw_height; i++)
//              {
//                 memcpy(this_display_buffer+j,buffer+k,width_offset_l*pixel_size);
//                 k = k + width;
//                 j = j + draw_width;
//              }
//             color_to_color(this_display_buffer,this_display_buffer,width_offset_l*height_offset_l,color_mode,obj->object_data_t.color_mode);//转换颜色模式
            
//             /*绘制显示对象*/
//             obj->set_coordinate(x_coordanate,y_coordinate,draw_width,draw_height); //向显示器发送绘制区域坐标信息    
//             obj->draw_object(this_display_buffer,color_mode);                      //绘制显示器缓冲区
//         }
//     }
//      if(use == 1) lock1++;
//      else lock2++;
// }

