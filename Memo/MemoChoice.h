class MemoStore;

class MemoChoice {
public:
	std::string title;
	bool (*method)(MemoStore& memos);
};