����װ�� ------> ������ɫ�� ------> ��դ�����ӿڱ任�� ------> ������ɫ�� ------> ����ϲ���ģ����ԡ���Ȳ��ԡ���ϲ�����

ECS(ʵ�����ϵͳ):https://blog.csdn.net/qq_52855744/article/details/125802048

CompoentBase(���࣬virtual void tick() = 0)
TransformComponent�̳���CompoentBase��position, ��дtick������
ModelComponentCompoentBase��mesh, ��дtick������

GameObject�ɶ��Component��ɣ�std::vector<CompoentBase*>��
					