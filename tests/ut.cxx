#include <mpi.h>
#include <gtest/gtest.h>

int main(int argc, char **argv) {

  MPI_Init(NULL,NULL);

  // Only get print from root
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  int rank; MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  if( rank != 0 ) {
      delete listeners.Release(listeners.default_result_printer());
  }

  // Init GT and run tests
  ::testing::InitGoogleTest(&argc, argv);
  auto gt_return = RUN_ALL_TESTS();

  MPI_Finalize();

  return gt_return; // return GT result

}
