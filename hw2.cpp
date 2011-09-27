#include "cvhw.h"

//a binary image (threshold at 128)
void CVHW::binary(int threshold)
{
	int m = image.rows;
	int n = image.cols;
	//int a,b;
	//a=b=0;
	printf("binary\n");
	printf("Threshold is %d\n",threshold);
	for ( int i = 0 ; i<m ; i++ )
	{
		for ( int j = 0 ; j<n ; j++ )
		{
			//printf("%d ",get_pix(i,j));
			if ( get_pix(i,j)>=threshold )
			{
				//a++;
				set_pix(i,j,255);
			}
			else
			{
				//b++;
				set_pix(i,j,0);
			}
		}
	}
	//printf("%d,%d\n",a,b);
}

//a histogram, return an array pointer
int* CVHW::histogram( )
{
	int* histogram_array=new int[256];
	int m = image.rows;
	int n = image.cols;

	printf("histogram\n");
	for ( int i = 0 ; i<256 ; i++ )
	{
		histogram_array[i]=0;
	}
	for ( int i=0 ; i<m ; i++ )
	{
		for ( int j=0 ; j<n ; j++ )
		{
			histogram_array[get_pix(i,j)]++;
		}
	}
	return histogram_array;
}

void CVHW::count_run ( )
{
	int m = image.rows;
	int n = image.cols;
	runs = 0;
	bool flag;
	for ( int i = 0 ; i<m ; i++ )
	{
		flag = false;
		for ( int j=0 ; j<n ; j++) 
		{
			printf("%d",get_pix(i,j)>0?1:0);
			if ( get_pix(i,j) > 0 && flag ==false) //meet the first 1 of a new run, mark flag as true
			{
				flag = true;
				runs++;
			}
			else if ( get_pix(i,j) == 0 && flag==true )
			{
				flag = false; //end of a run, mark flag as false;
			}
		}
		printf("\n");
	}
}

void CVHW::initialize_run_table( )
{
	int m = image.rows;
	int n = image.cols;

	row_start = new int[m];
	row_end = new int[m];
	
	row = new int[runs+1];
	start_col = new int[runs+1];
	end_col = new int[runs+1];
	perm_label = new int[runs+1];
	label = new int[runs+1];
	next = new int[runs+1];
	eq_class = new int[runs+1];

	bool flag;
	int num_runs = 0;
	for ( int i = 0 ; i<m ; i++ )
	{
		flag = false;
		row_start[i] = row_end[i] = 0;
		for ( int j=0 ; j<n ; j++) 
		{
			if ( get_pix(i,j) > 0 && flag ==false) //meet the first 1 of a new run, mark flag as true
			{
				flag = true;
				num_runs++;
				//update run table
				if ( row_start[i]==0 ) row_start[i] = num_runs; //update row_start[i];
				row_end[i] = num_runs; //update row_end[i];
				row[num_runs] = i; //initialize row
				start_col[num_runs] = j; //initialize start_col
				perm_label[num_runs] = 0; //initialize perm_label
				label[num_runs] = 0; //initialize label
				next[num_runs] = 0; //initialize next
				eq_class[num_runs] = 0; //initialize eq_class
			}
			else if ( get_pix(i,j) == 0 && flag==true )
			{
				flag = false; //end of a run, mark flag as false;
				end_col[num_runs]=j-1; //initialize end_col
			}
		}
		if ( flag )
		{
			end_col[num_runs]=n-1;
		}
	}
}

void CVHW::make_equivalent(int i1 , int i2)
{
	if ( label[i1] == 0 && label[i2] == 0 )
	{
		label[i1]=label[i2]=i1;
		next[i1] = i2;
		next[i2] = 0;
		eq_class[i1]=i1;
	}
	else if ( label[i1]==label[i2] )
	{
		return ;
	}
	else if ( label[i1]!=0 && label[i2]==0 )
	{
		int beginning  = label[i1];
		label[i2]=beginning;
		next[i2] = eq_class[beginning];
		eq_class[beginning]=i2;
	}
	else if ( label[i1]==0 && label[i2]!=0 )
	{
		int beginning  = label[i2];
		label[i1]=beginning;
		next[i1] = eq_class[beginning];
		eq_class[beginning]=i1;
	}
	else if ( label[i1]!=0 && label[i2]!=0 )
	{
		int beginning = label[i2];
		int member = eq_class[beginning];
		int eq_label = label[i1];
		while ( next[member] )
		{
			label[member]=eq_label;
			member=next[member];
		}
		label[member]=eq_label;
		next[member] = eq_class[eq_label];
		eq_class[eq_label]=eq_class[beginning];
		eq_class[beginning] = 0;
	}
	return ;
}

void CVHW::run_length ( )
{
	int m = image.rows;
	int n = image.cols;
	int p,q,plast,qlast;
	int new_label=0;
	count_run(); //count run

	

	//initialize run_table
	initialize_run_table( );

	//top-down pass
	for ( int i = 0 ; i<m ; i++ )
	{
		p = row_start[i];
		plast = row_end[i];

		if ( i==0 )
		{
			q=qlast = 0;/*
			while ( p<=plast )
			{
				perm_label[p]=p;
				p++;
			}*/
		}
		else
		{
			q=row_start[i-1], qlast=row_end[i-1];
		}
		while ( p<=plast && q<=qlast && q )
		{
			if ( end_col[p] < start_col[q] ) p++;
			else if ( end_col[q]<start_col[p] ) q++;
			else
			{
				int plabel = perm_label[p];
				if ( plabel == 0 ) 
					perm_label[p] = perm_label[q];
				else if ( plabel && perm_label[q]!=plabel )
					make_equivalent(perm_label[p],perm_label[q]);
				if ( end_col[p] > end_col[q] )	
					q++;
				else if ( end_col[q] > end_col[p] )
					p++;
				else if ( end_col[q] == end_col[p] )
					q++,p++;
			}
		}

		p = row_start[i];
		while(p<=plast)
		{
			int plabel = perm_label[p];
			if ( plabel == 0 )
			{
				perm_label[p] = ++new_label;
			}
			else if ( plabel && label[plabel] )
			{
				perm_label[p] = label[plabel];
			}
			p++;
		}
	}

	//bottom-up pass
	for  ( int i=m-1 ; i>=0 ; i-- )
	{
		p = row_start[i];
		plast = row_end[i];
		if ( i == m-1 )
		{
			q=qlast = 0;
		}
		else
		{
			q=row_start[i+1];
			qlast = row_end[i+1];
		}
		if ( p && q )
		{

		}
		while ( p<=plast && q<=qlast && q )
		{
			if ( end_col[p] < start_col[q] ) p++;
			else if ( end_col[q]<start_col[p] ) q++;
			else
			{
				if ( perm_label[p]!=perm_label[q] )
				{
					label[perm_label[p]]=perm_label[q];
					perm_label[p] = perm_label[q];
				}

				if  ( end_col[p] > end_col[q] ) q++;
				else if ( end_col[q] > end_col[p] ) p++;
				else if ( end_col[p] == end_col[q] ) q++,p++;
			}
		}
		p=row_start[i];
		while ( p<=plast )
		{
			if ( label[perm_label[p]] )
			{
				perm_label[p] =label[perm_label[p]];
			}
			p++;
		} 
	}
}

void CVHW::classic_connected_components( )
{

}

void CVHW::draw_bounding_box ( BOUNDING_BOX&  box )
{
	for ( int i = box.top_left_x ; i<=box.bottom_right_x ; i++ ) // draw |
	{
		set_pix(i,box.top_left_y,GRAY);
		set_pix(i,box.bottom_right_y,GRAY);
	}

	for ( int i = box.top_left_y ; i<= box.bottom_right_y ; i++ )
	{
		set_pix(box.top_left_x,i,GRAY);
		set_pix(box.bottom_right_x,i,GRAY);
	}
}

void CVHW::connected_components( int threshold )
{
	binary( );
	run_length();
	std::map<int,BOUNDING_BOX> pixel_in_component;
	std::vector<BOUNDING_BOX> draw_bounding_boxes;
	
	//count how many connected components
	for ( int i = 1 ; i<=runs ; i++ )
	{
		pixel_in_component[perm_label[i]].sum_pixel+=end_col[i]-start_col[i];
		if ( pixel_in_component[perm_label[i]].top_left_x < 0 )
			pixel_in_component[perm_label[i]].top_left_x = row[i];
		if ( pixel_in_component[perm_label[i]].top_left_y < 0 || pixel_in_component[perm_label[i]].top_left_y > start_col[i] )
			pixel_in_component[perm_label[i]].top_left_y = start_col[i];
		if ( pixel_in_component[perm_label[i]].bottom_right_x < row[i] )
			pixel_in_component[perm_label[i]].bottom_right_x = row[i];
		if ( pixel_in_component[perm_label[i]].bottom_right_y < end_col[i] )
			pixel_in_component[perm_label[i]].bottom_right_y = end_col[i];
	}

	//fliter small connected componets
	for ( std::map<int,BOUNDING_BOX>::iterator iter= pixel_in_component.begin(); iter != pixel_in_component.end() ; iter++ )
	{
		if ( iter->second.sum_pixel >= threshold )
		{
			draw_bounding_boxes.push_back(iter->second);
		}
	}

	for ( std::vector<BOUNDING_BOX>::iterator iter = draw_bounding_boxes.begin(); iter!=draw_bounding_boxes.end() ; iter++ )
	{
		draw_bounding_box(*iter);
	}
}