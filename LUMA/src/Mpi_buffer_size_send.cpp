/*
 * --------------------------------------------------------------
 *
 * ------ Lattice Boltzmann @ The University of Manchester ------
 *
 * -------------------------- L-U-M-A ---------------------------
 *
 *  Copyright (C) 2015, 2016
 *  E-mail contact: info@luma.manchester.ac.uk
 *
 * This software is for academic use only and not available for
 * distribution without written consent.
 *
 */

#include "../inc/stdafx.h"
#include <mpi.h>
#include "../inc/MpiManager.h"
#include "../inc/GridObj.h"
#include "../inc/GridUtils.h"


// ****************************************************************************
/// \brief	Method to pre-compute the size of the sender layer buffer.
///
///			A halo consists of a receiver (outer) and sender (inner) layer. 
///			This method computes the size of the sender layers in each 
///			communication direction (MPI directions).
///
/// \param	g	grid being inspected.
void MpiManager::mpi_buffer_size_send(GridObj*& g) {
	
	int count, i, j, k, dir;	// Local counters
	// Local grid sizes
	int N_lim = static_cast<int>(g->XInd.size()), M_lim = static_cast<int>(g->YInd.size())
#if (L_dims == 3)
		, K_lim = static_cast<int>(g->ZInd.size());
#else
		, K_lim = 1;
#endif

	/* Loop over the allowable directions:
	* 0		=	Right
	* 1		=	Left
	* 2		=	Right-Up
	* 3		=	Left-Down
	* 4		=	Up
	* 5		=	Down
	* 6		=	Left-Up
	* 7		=	Right-Down
	* -------- 3D --------
	* 8		=	Back
	* 9		=	Front
	* 10	=	Right-Back
	* 11	=	Left-Front
	* 12	=	Right-Up-Back
	* 13	=	Left-Down-Front
	* 14	=	Up-Back
	* 15	=	Down-Front
	* 16	=	Left-Up-Back
	* 17	=	Right-Down-Front
	* 18	=	Left-Back
	* 19	=	Right-Front
	* 20	=	Left-Down-Back
	* 21	=	Right-Up-Front
	* 22	=	Down-Back
	* 23	=	Up-Front
	* 24	=	Right-Down-Back
	* 25	=	Left-Up-Front
	*/
	for (dir = 0; dir < L_MPI_dir; dir++)  {

		// Reset the site counter
		count = 0;

		// Switch based on direction
		switch (dir)
		{

		case 0:
			// Right

			// Examine possible inner and outer buffer locations
			for (range_i_right) {
				for (j = 0; j < M_lim; j++) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum) && 
								(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum))
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 1:
			// Left
			for (range_i_left) {
				for (j = 0; j < M_lim; j++) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum) && 
								(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum))
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 2:
			// Right-Up
			for (range_i_right) {
				for (range_j_up) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum) && 
								GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 3:
			// Left-Down
			for (range_i_left) {
				for (range_j_down) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum) && 
								GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 4:
			// Up
			for (i = 0; i < N_lim; i++) {
				for (range_j_up) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) &&
								GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;


		case 5:
			// Down
			for (i = 0; i < N_lim; i++) {
				for (range_j_down) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) &&
								GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 6:
			// Left-Up
			for (range_i_left) {
				for (range_j_up) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum) && 
								GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 7:
			// Right-Down
			for (range_i_right) {
				for (range_j_down) {
					for (k = 0; k < K_lim; k++) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if (  GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum) && 
								GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)
#if (L_dims == 3)
								&&
								(!GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMaximum) && !GridUtils::isOnRecvLayer(g->ZPos[k],eZDirection,eMinimum))
#endif
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;


		///////////////////////
		// 3D-specific cases //
		///////////////////////

		case 8:
			// Back
			for (i = 0; i < N_lim; i++) {
				for (j = 0; j < M_lim; j++) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 9:
			// Front
			for (i = 0; i < N_lim; i++) {
				for (j = 0; j < M_lim; j++) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 10:
			// Right-Back
			for (range_i_right) {
				for (j = 0; j < M_lim; j++) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 11:
			// Left-Front
			for (range_i_left) {
				for (j = 0; j < M_lim; j++) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum)) && 
									(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 12:
			// Right-Up-Back
			for (range_i_right) {
				for (range_j_up) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 13:
			// Left-Down-Front
			for (range_i_left) {
				for (range_j_down) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 14:
			// Up-Back
			for (i = 0; i < N_lim; i++) {
				for (range_j_up) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 15:
			// Down-Front
			for (i = 0; i < N_lim; i++) {
				for (range_j_down) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 16:
			// Left-Up-Back
			for (range_i_left) {
				for (range_j_up) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 17:
			// Right-Down-Front
			for (range_i_right) {
				for (range_j_down) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 18:
			// Left-Back
			for (range_i_left) {
				for (j = 0; j < M_lim; j++) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum)) && 
									(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 19:
			// Right-Front
			for (range_i_right) {
				for (j = 0; j < M_lim; j++) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(!GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 20:
			// Left-Down-Back
			for (range_i_left) {
				for (range_j_down) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 21:
			// Right-Up-Front
			for (range_i_right) {
				for (range_j_up) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 22:
			// Down-Back
			for (i = 0; i < N_lim; i++) {
				for (range_j_down) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 23:
			// Up-Front
			for (i = 0; i < N_lim; i++) {
				for (range_j_up) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (!GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMinimum) && !GridUtils::isOnRecvLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 24:
			// Right-Down-Back
			for (range_i_right) {
				for (range_j_down) {
					for (range_k_back) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMaximum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMinimum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMaximum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		case 25:
			// Left-Up-Front
			for (range_i_left) {
				for (range_j_up) {
					for (range_k_front) {

						// Check conditions for sender
						if (g->LatTyp(i,j,k,M_lim,K_lim) != eRefined)	// Do not pass refined sites as zero anyway
						{
							if ( (GridUtils::isOnSenderLayer(g->XPos[i],eXDirection,eMinimum)) && 
									(GridUtils::isOnSenderLayer(g->YPos[j],eYDirection,eMaximum)) &&
									(GridUtils::isOnSenderLayer(g->ZPos[k],eZDirection,eMinimum))
							) {
								// Must be a site to pass in MPI so increment counter
								count++;
							}
						}

					}
				}
			}
			break;

		default:
			std::cout << "Unidentified direction: " << dir << std::endl;
			break;
		}
			
		// Store the count of sites in the MpiManager buffer_info structure
		buffer_send_info.back().size[dir] = count;				

	}

}