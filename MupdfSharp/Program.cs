using System;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;
using CC = System.Runtime.InteropServices.CallingConvention;

namespace MupdfSharp
{
	class Program
	{
		static void Main (string[] args) {
			IntPtr ctx = NativeMethods.NewContext (); // Creates the context
			IntPtr stm = NativeMethods.OpenFile (ctx, "test.pdf"); // opens file test.pdf as a stream
			IntPtr doc = NativeMethods.OpenDocumentStream (ctx, stm); // opens the document
			int pn = NativeMethods.CountPages (ctx, doc); // gets the number of pages in the document
			for (int i = 0; i < pn; i++) { // iterate through each pages
				Console.WriteLine ("Rendering page " + (i + 1));
				IntPtr p = NativeMethods.LoadPage (ctx, doc, i); // loads the page (first page number is 0)
				Rectangle b = new Rectangle ();
				NativeMethods.BoundPage (ctx, p, ref b); // gets the page size

				using (var bmp = RenderPage (ctx, doc, p, b)) { // renders the page and converts the result to Bitmap
					Console.WriteLine ("Saving picture: " + (i+1) + ".png");
					bmp.Save ((i+1) + ".png"); // saves the bitmap to a file
				}
				NativeMethods.DropPage (ctx, p); // releases the resources consumed by the page
			}
			NativeMethods.DropDocument (ctx, doc); // releases the resources
			NativeMethods.DropStream (ctx, stm);
			NativeMethods.DropContext (ctx);
			Console.WriteLine ("Program finished. Press any key to quit.");
			Console.ReadKey (true);
		}

		static Bitmap RenderPage (IntPtr context, IntPtr document, IntPtr page, Rectangle pageBound) {
			Matrix ctm = new Matrix ();
			IntPtr pix = IntPtr.Zero;
			IntPtr dev = IntPtr.Zero;

			int width = (int)(pageBound.Right - pageBound.Left); // gets the size of the page
			int height = (int)(pageBound.Bottom - pageBound.Top);
			ctm.A = ctm.D = 1; // sets the matrix as the identity matrix (1,0,0,1,0,0)

			// creates a pixmap the same size as the width and height of the page
			pix = NativeMethods.NewPixmap (context, NativeMethods.FindDeviceColorSpace (context, ColorSpace.Rgb), width, height, IntPtr.Zero, 0);
			// sets white color as the background color of the pixmap
			NativeMethods.ClearPixmap (context, pix, 0xFF);

			// creates a drawing device
			var im = Matrix.Identity;
			dev = NativeMethods.NewDrawDevice (context, ref im, pix);
			// draws the page on the device created from the pixmap
			NativeMethods.RunPage (context, page, dev, ref ctm, IntPtr.Zero);

			NativeMethods.CloseDevice(context, dev);
			NativeMethods.DropDevice (context, dev); // frees the resources consumed by the device
			dev = IntPtr.Zero;

			// creates a colorful bitmap of the same size of the pixmap
			Bitmap bmp = new Bitmap (width, height, PixelFormat.Format24bppRgb); 
			var imageData = bmp.LockBits (new System.Drawing.Rectangle (0, 0, width, height), ImageLockMode.ReadWrite, bmp.PixelFormat);
			unsafe { // converts the pixmap data to Bitmap data
				byte* ptrSrc = (byte*)NativeMethods.GetSamples (context, pix); // gets the rendered data from the pixmap
				byte* ptrDest = (byte*)imageData.Scan0;
				for (int y = 0; y < height; y++) {
					byte* pl = ptrDest;
					byte* sl = ptrSrc;
					for (int x = 0; x < width; x++) {
						//Swap these here instead of in MuPDF because most pdf images will be rgb or cmyk.
						//Since we are going through the pixels one by one anyway swap here to save a conversion from rgb to bgr.
						pl[2] = sl[0]; //b-r
						pl[1] = sl[1]; //g-g
						pl[0] = sl[2]; //r-b
						pl += 3;
						sl += 3;
					}
					ptrDest += imageData.Stride;
					ptrSrc += width * 3;
				}
			}
			NativeMethods.DropPixmap (context, pix);
			return bmp;
		}

		public enum ColorSpace
		{
			Rgb,
			Bgr,
			Cmyk,
			Gray
		}
		class NativeMethods
		{
			const uint FZ_STORE_DEFAULT = 256 << 20;
			const string DLL = "MuPDFLib.dll";
			// please modify the version number to match the FZ_VERSION definition in "fitz\version.h" file
			const string FZ_VERSION = "1.12.0";

			[DllImport(DLL, EntryPoint = "fz_new_context_imp", CallingConvention = CC.Cdecl, BestFitMapping = false)]
			static extern IntPtr NewContext(IntPtr alloc, IntPtr locks, uint max_store, [MarshalAs(UnmanagedType.LPStr)] string fz_version);

			internal static IntPtr NewContext() {
				var c = NewContext(IntPtr.Zero, IntPtr.Zero, FZ_STORE_DEFAULT, FZ_VERSION);
				if (c == IntPtr.Zero) {
					throw new InvalidOperationException("Version number mismatch.");
				}
				return c;
			}

			[DllImport(DLL, EntryPoint = "fz_drop_context", CallingConvention = CC.Cdecl)]
			internal static extern void DropContext(IntPtr ctx);

			[DllImport (DLL, EntryPoint = "fz_open_file_w", CharSet = CharSet.Unicode)]
			public static extern IntPtr OpenFile (IntPtr ctx, string fileName);

			[DllImport (DLL, EntryPoint = "pdf_open_document_with_stream")]
			public static extern IntPtr OpenDocumentStream (IntPtr ctx, IntPtr stm);

			[DllImport (DLL, EntryPoint = "fz_drop_stream")]
			public static extern IntPtr DropStream (IntPtr ctx, IntPtr stm);

			[DllImport (DLL, EntryPoint = "pdf_drop_document")]
			public static extern IntPtr DropDocument (IntPtr ctx, IntPtr doc);

			[DllImport (DLL, EntryPoint = "pdf_count_pages")]
			public static extern int CountPages (IntPtr ctx, IntPtr doc);

			[DllImport (DLL, EntryPoint = "pdf_bound_page")]
			public static extern void BoundPage (IntPtr ctx, IntPtr page, ref Rectangle bound);

			[DllImport (DLL, EntryPoint = "fz_clear_pixmap_with_value")]
			public static extern void ClearPixmap (IntPtr ctx, IntPtr pix, int byteValue);

			public static IntPtr FindDeviceColorSpace(IntPtr context, ColorSpace colorspace) {
				switch (colorspace) {
					case ColorSpace.Rgb: return GetRgbColorSpace(context);
					case ColorSpace.Bgr: return GetBgrColorSpace(context);
					case ColorSpace.Cmyk: return GetCmykColorSpace(context);
					case ColorSpace.Gray: return GetGrayColorSpace(context);
					default: throw new NotImplementedException(colorspace + " not supported.");
				}
			}
			[DllImport(DLL, EntryPoint = "fz_device_gray", CallingConvention = CC.Cdecl)]
			public static extern IntPtr GetGrayColorSpace(IntPtr ctx);
			[DllImport(DLL, EntryPoint = "fz_device_rgb", CallingConvention = CC.Cdecl)]
			public static extern IntPtr GetRgbColorSpace(IntPtr ctx);
			[DllImport(DLL, EntryPoint = "fz_device_bgr", CallingConvention = CC.Cdecl)]
			public static extern IntPtr GetBgrColorSpace(IntPtr ctx);
			[DllImport(DLL, EntryPoint = "fz_device_cmyk", CallingConvention = CC.Cdecl)]
			public static extern IntPtr GetCmykColorSpace(IntPtr ctx);

			[DllImport(DLL, EntryPoint = "fz_close_device")]
			public static extern void CloseDevice(IntPtr ctx, IntPtr dev);
			[DllImport (DLL, EntryPoint = "fz_drop_device")]
			public static extern void DropDevice (IntPtr ctx, IntPtr dev);

			[DllImport (DLL, EntryPoint = "fz_drop_page")]
			public static extern void DropPage (IntPtr ctx, IntPtr page);

			[DllImport (DLL, EntryPoint = "pdf_load_page")]
			public static extern IntPtr LoadPage (IntPtr ctx, IntPtr doc, int pageNumber);

			[DllImport (DLL, EntryPoint = "fz_new_draw_device")]
			public static extern IntPtr NewDrawDevice (IntPtr ctx, ref Matrix matrix, IntPtr pix);

			[DllImport (DLL, EntryPoint = "fz_new_pixmap")]
			public static extern IntPtr NewPixmap (IntPtr ctx, IntPtr colorspace, int width, int height, IntPtr separation, int alpha);

			[DllImport (DLL, EntryPoint = "pdf_run_page")]
			public static extern void RunPage (IntPtr ctx, IntPtr page, IntPtr dev, ref Matrix transform, IntPtr cookie);

			[DllImport (DLL, EntryPoint = "fz_drop_pixmap")]
			public static extern void DropPixmap (IntPtr ctx, IntPtr pix);

			[DllImport (DLL, EntryPoint = "fz_pixmap_samples")]
			public static extern IntPtr GetSamples (IntPtr ctx, IntPtr pix);

		}
	}
}
