// { dg-do assemble  }
// Error: Internal compiler error in 2.7.2 & EGCS 1.0.0

template <int nlimb, int i>
inline unsigned f (unsigned* ptr);
template <int nlimb>
inline unsigned f<nlimb,nlimb> (unsigned* ptr) // { dg-error "partial specialization" }
{
  return 1;
}

