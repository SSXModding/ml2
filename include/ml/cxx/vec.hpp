#ifndef ML_VEC_HPP
#define ML_VEC_HPP

#include <ml/libc_wrappers.h>
#include <ml/types.h>

#include <new>

/// A vector.
template <class T>
struct mlVec {
	typedef T* Pointer;
	typedef T& Reference;
	typedef const T& ConstReference;
	typedef usize SizeType;

	mlVec() {
		pMemory = nil(T*);
		uiCapacity = 0;
		uiSize = 0;
	}

	mlVec(const mlVec& vec) {
		Resize(vec.uiSize);
		for(SizeType i = 0; i < vec.uiSize; ++i)
			new(&this->pMemory[i]) T(vec.pMemory[i]);
	}

	void Reserve(SizeType newCapacity) {
		if(newCapacity == 0) {
			if(uiCapacity != 0) {
				destroy(pMemory, uiCapacity);
				// Reset
				pMemory = nil(T*);
				uiCapacity = 0;
				uiSize = 0;
			}
		} else if(newCapacity < uiCapacity) {
			return;
		}

		Pointer pOldMemory = pMemory;
		SizeType oldCapacity = uiCapacity;

		pMemory = (T*)mlMalloc(newCapacity * sizeof(T));

		if(pOldMemory) {
			// Initialize previous elements via copy-construction
			for(SizeType i = 0; i < oldCapacity; ++i)
				new(&pMemory[i]) T(pOldMemory[i]);

			// Initalize newly reserved elements with default construction
			for(SizeType i = oldCapacity; i < newCapacity; ++i)
				new(&pMemory[i]) T();

			destroy(pOldMemory, oldCapacity);
		} else {
			for(SizeType i = 0; i < newCapacity; ++i)
				new(&pMemory[i]) T();
		}

		uiCapacity = newCapacity;
	}

	void Resize(SizeType uiNewSize) {
		if(uiNewSize > uiCapacity) {
			Reserve(uiNewSize + 4);
		} else {
			// End lifetime of objects we no longer need.
			for(SizeType i = uiNewSize; i < uiSize; ++i)
				pMemory[i].~T();
		}

		uiSize = uiNewSize;
	}

	void pushBack(ConstReference item) {
		Resize(uiSize + 1);
		pMemory[uiSize - 1] = item;
	}

	void Clear() {
		Resize(0);
	}

	Reference operator[](SizeType index) {
		return pMemory[index];
	}

	ConstReference operator[](SizeType index) const {
		return pMemory[index];
	}

	SizeType Capacity() const {
		return uiCapacity;
	}
    
	SizeType Size() const {
		return uiSize;
	}

   private:
	void destroy(T* pMemToDestroy, SizeType len) {
		for(SizeType i = 0; i < len; ++i)
			pMemToDestroy[i].~T();
		mlFree(pMemToDestroy);
	}

	T* pMemory;
	SizeType uiCapacity; // In elements of T
	SizeType uiSize;	 // Actual size.
};

#endif