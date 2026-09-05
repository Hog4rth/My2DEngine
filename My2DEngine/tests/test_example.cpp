#include <gtest/gtest.h>
#include "../FileManager.h"

TEST(FileManagerTest, FallbackOnMissingKey) {
	// Simuliamo la richiesta di un file inesistente
	FileManager fm("file_fake.ini");
	fm.LoadFile();

	// Verifichiamo che il sistema di fallback restituisca i valori di default passati
	int fallbackInt = fm.Load<int>("FakeSpeed", 100);
	float fallbackFloat = fm.Load<float>("FakeGravity", 9.81f);

	EXPECT_EQ(fallbackInt, 100);
	EXPECT_FLOAT_EQ(fallbackFloat, 9.81f);
}
