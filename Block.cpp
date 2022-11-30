#include "Block.h"
#include "sha256.h"

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
	_nRandomness = 0;
	_tTime = time(nullptr);

	sHash = _CalculateHashPrev();
}

void Block::MineBlock(uint32_t nDifficulty)
{
	char cstr[nDifficulty + 1];
	for (uint32_t i = 0; i < nDifficulty; ++i)
	{
		cstr[i] = '0';
	}
	cstr[nDifficulty] = '\0';

	string str(cstr);

	do
	{
		_nRandomness++;
		sHash = _CalculateHashPrev();
	} while (sHash.substr(0, nDifficulty) != str);

	cout << "Block mined: " << sHash << endl;
}

inline string Block::_CalculateHashPrev() const
{
	stringstream ss;
	ss << _nIndex << sPrevHash << _tTime << _sData << _nRandomness;

	return sha256(ss.str());
}

inline string Block::_CalculateHashNext() const
{
	stringstream ss;
	ss << _nIndex << sPrevHash << _tTime << _sData;

	return sha256(ss.str());
}

void Block::UpdateRandomness(uint32_t nRandomnessIn)
{
	_nRandomness = nRandomnessIn;
}