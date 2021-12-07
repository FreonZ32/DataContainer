void main()
{
	int a = 0;
	std::thread hello_thread(thr1, ref(a));
	std::thread world_thread(thr2);

	cin.get();
	finish = true;

	world_thread.join();
	hello_thread.join();
}