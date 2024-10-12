枚举的相关事项：
1.枚举的底层类型是int，如果要修改，也只能修改成其他的整数类型（char short int long）
2.枚举的默认值从0开始，但是可以人为指定成其他的值
3.主要的应用：表示选项（如开关的开和关，游戏角色的状态），表示星期几
enum DAY{             int main(){
   Sunday,               enum Day today;
   Monday,               today=Sunday;
   Tuesday,              printf("%d",today);
   Wednesday,            return 0;
   Thursday,         }
   Friday,
   Saturday
};
