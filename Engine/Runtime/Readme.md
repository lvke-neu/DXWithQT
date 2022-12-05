输入装配 ------> 顶点着色器 ------> 光栅化（视口变换） ------> 像素着色器 ------> 输出合并（模板测试→深度测试→混合操作）

ECS(实体对象系统):https://blog.csdn.net/qq_52855744/article/details/125802048

CompoentBase(基类，virtual void tick() = 0)
TransformComponent继承自CompoentBase（position, 重写tick函数）
ModelComponentCompoentBase（mesh, 重写tick函数）

GameObject由多个Component组成（std::vector<CompoentBase*>）


!!!!!!!!!!!!!!!!!!!!!!!!!!!
写bindable模块的时候太困了，基类析构函数忘记写virtual了导致内存泄漏（在每一帧读取纹理，很快内存就满了）
					