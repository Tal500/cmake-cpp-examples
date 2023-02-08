#include <cstddef>
#include <vector>
#include <string>

/**
 * Storage for the user memos.
 */
class MemoStore {
public:

	/**
	 * @return The top memo in the store (the last in the storage).
	 */
	const std::string& topMemo() const;

	/**
	 * @param index The place to retrieve from.
	 * @return The top memo in a specific place.
	 */
	const std::string& getMemo(int index) const;

	/**
	 * @return The amount of memos currently in the storage.
	 */
	std::size_t size() const;

	/**
	 * @return If the store is empty or not
	 */
	bool empty() const;

	/**
	 * Pushing a memo to the list.
	 * @param memo The memo to push.
	 */
	void pushMemo(const std::string& memo);

	/**
	 * Get a memo from a specific location in the storage, and removing it.
	 * @param index The place to retrieve from.
	 * @return The memo on that location (which was removed).
	 */
	std::string fetchMemo(int index);
private:
	std::vector<std::string> _memos;
};